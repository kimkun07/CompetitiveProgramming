#include "json/json.h"
#include <bits/stdc++.h>
#include <curl/curl.h>

using namespace std;

#pragma region libcurl
size_t WriteCallback(char *curl_data, size_t itemSize, size_t nitems,
                     string *readBuffer) {
  size_t bytes = itemSize * nitems;
  readBuffer->append(curl_data, bytes);

  // Tell libcurl that we processed all bytes in current chunk
  return itemSize * nitems;
}

string rest_get(const string &url) {
  CURL *curl = curl_easy_init();
  if (not curl) {
    throw "curl_easy_init() failed";
  }

  string readBuffer;
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

  CURLcode result = curl_easy_perform(curl);
  if (result != CURLE_OK) {
    throw "curl_easy_perform() failed: " + string(curl_easy_strerror(result));
  }

  curl_easy_cleanup(curl);
  return readBuffer;
}

string rest_post(const string &url, const string &jsonString) {
  CURL *curl = curl_easy_init();
  if (not curl) {
    throw "curl_easy_init() failed";
  }

  struct curl_slist *headers = nullptr;
  headers = curl_slist_append(headers, "Content-Type: application/json");

  string readBuffer;
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

  CURLcode result = curl_easy_perform(curl);
  if (result != CURLE_OK) {
    throw "curl_easy_perform() failed: " + string(curl_easy_strerror(result));
  }

  curl_easy_cleanup(curl);
  curl_slist_free_all(headers);
  return readBuffer;
}
#pragma endregion

#pragma region jsoncpp
string json_to_jsonString(const Json::Value &jsonValue) {
  Json::StreamWriterBuilder builder;
  return Json::writeString(builder, jsonValue);
}

Json::Value jsonString_to_json(const string &jsonString) {
  istringstream istream(jsonString);
  Json::CharReaderBuilder builder;
  Json::Value rootJson;
  string errs;

  if (Json::parseFromStream(builder, istream, &rootJson, &errs)) {
    return rootJson;
  } else {
    throw "Cannot parse jsonString:" + jsonString;
  }
}
#pragma endregion

#pragma region Application GET
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

  static Data fromJson(const Json::Value &jsonValue) {
    Data data{
        .id = jsonValue["id"].asInt(),
        .email = jsonValue["email"].asString(),
        .first_name = jsonValue["first_name"].asString(),
        .last_name = jsonValue["last_name"].asString(),
        .avatar = jsonValue["avatar"].asString(),
    };
    return data;
  }
};
struct Support {
  string url;
  string text;

  string toString() { return "Support(url=" + url + ", text=" + text + ")"; }

  static Support fromJson(const Json::Value &jsonValue) {
    Support support{
        .url = jsonValue["url"].asString(),
        .text = jsonValue["text"].asString(),
    };
    return support;
  }
};
struct User {
  Data data;
  Support support;

  string toString() {
    return "User(\n  " + data.toString() + "\n  " + support.toString() + "\n)";
  }
  static User fromJson(const Json::Value &jsonValue) {
    Data data = Data::fromJson(jsonValue["data"]);
    Support support = Support::fromJson(jsonValue["support"]);
    User user{.data = data, .support = support};
    return user;
  }
};
#pragma endregion

#pragma region Application POST
struct PostData {
  string name;
  string job;

  Json::Value toJson() {
    Json::Value jsonValue;
    jsonValue["name"] = name;
    jsonValue["job"] = job;
    return jsonValue;
  }
};
struct PostResponse {
  string name;
  string job;
  string id;
  string createdAt;

  string toString() {
    return "PostResponse(name=" + name + ", job=" + job + ", id=" + id +
           ", createdAt=" + createdAt + ")";
  }

  static PostResponse fromJson(const Json::Value &jsonValue) {
    PostResponse response{
        .name = jsonValue["name"].asString(),
        .job = jsonValue["job"].asString(),
        .id = jsonValue["id"].asString(),
        .createdAt = jsonValue["createdAt"].asString(),
    };
    return response;
  }
};
#pragma endregion

int main() {
  // GET
  string get_jsonString = rest_get("https://reqres.in/api/users/2");
  User user = User::fromJson(jsonString_to_json(get_jsonString));
  cout << user.toString() << endl;

  // POST
  PostData newUser{.name = "morpheus", .job = "leader"};
  string jsonString = json_to_jsonString(newUser.toJson());

  string post_jsonString = rest_post("https://reqres.in/api/users", jsonString);
  PostResponse postResponse =
      PostResponse::fromJson(jsonString_to_json(post_jsonString));
  cout << postResponse.toString() << endl;
  return 0;
}
