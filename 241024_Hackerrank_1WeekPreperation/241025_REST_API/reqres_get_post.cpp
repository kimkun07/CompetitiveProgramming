#include "json/json.h"
#include <bits/stdc++.h>
#include <curl/curl.h>

using namespace std;

size_t WriteCallback(char *curl_data, size_t itemSize, size_t nitems,
                     string *readBuffer) {
  size_t bytes = itemSize * nitems;
  readBuffer->append(curl_data, bytes);

  // Tell libcurl that we processed all bytes in current chunk
  return itemSize * nitems;
}

string rest_get(const string &url) {
  CURL *curl = curl_easy_init();

  if (curl) {
    string readBuffer;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
      cerr << "curl_easy_perform() failed: " << curl_easy_strerror(result)
           << endl;
    }

    curl_easy_cleanup(curl);
    return readBuffer;
  } else {
    return string("");
  }
}

struct Data {
  int id;
  string email;
  string first_name;
  string last_name;
  string avatar;

  string toString() {
    return "Data(id=" + to_string(id) + ", email=" + email +
           ", first_name=" + first_name + ", last_name=" + last_name +
           ", avatar=" + avatar + ")";
  }
};
struct Support {
  string url;
  string text;

  string toString() { return "Support(url=" + url + ", text=" + text + ")"; }
};
struct User {
  Data data;
  Support support;

  string toString() {
    return "User(\n  " + data.toString() + "\n  " + support.toString() + "\n)";
  }
};

optional<User> parseJsonString(const string &jsonString) {
  istringstream istream(jsonString);
  Json::CharReaderBuilder builder;
  Json::Value rootJson;
  string errs;

  if (Json::parseFromStream(builder, istream, &rootJson, &errs)) {
    Json::Value dataJson = rootJson["data"];
    Data data{
        .id = dataJson["id"].asInt(),
        .email = dataJson["email"].asString(),
        .first_name = dataJson["first_name"].asString(),
        .last_name = dataJson["last_name"].asString(),
        .avatar = dataJson["avatar"].asString(),
    };

    Json::Value supportJson = rootJson["support"];
    Support support{.url = supportJson["url"].asString(),
                    .text = supportJson["text"].asString()};

    User user{.data = data, .support = support};
    return user;
  } else {
    cerr << "Failed to parse JSON: " << errs << endl;
    return nullopt;
  }
}

int main() {
  string response = rest_get("https://reqres.in/api/users/2");
  cout << "Raw JSON response: " << response << endl;

  optional<User> userOpt = parseJsonString(response);
  if (userOpt) {
    User user = *userOpt;
    cout << user.toString() << endl;
  } else {
    cerr << "Failed parsing" << endl;
  }
  return 0;
}
