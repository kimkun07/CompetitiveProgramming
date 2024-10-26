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

struct Todo {
  int userId;
  int id;
  string title;
  bool completed;

  void print() {
    cout << "User ID: " << userId << endl;
    cout << "ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Completed: " << boolalpha << completed << endl;
  }
};

optional<Todo> parseJsonString(const string &jsonString) {
  istringstream istream(jsonString);
  Json::CharReaderBuilder builder;
  Json::Value jsonValue;
  string errs;

  if (Json::parseFromStream(builder, istream, &jsonValue, &errs)) {
    Todo todo{.userId = jsonValue["userId"].asInt(),
              .id = jsonValue["id"].asInt(),
              .title = jsonValue["title"].asString(),
              .completed = jsonValue["completed"].asBool()};
    return todo;
  } else {
    cerr << "Failed to parse JSON: " << errs << endl;
    return nullopt;
  }
}

int main() {
  string response = rest_get("https://jsonplaceholder.typicode.com/todos/2");
  cout << "Raw JSON response: " << response << endl;

  optional<Todo> todoOpt = parseJsonString(response);
  if (todoOpt) {
    Todo todo = *todoOpt;
    todo.print();
  } else {
    cerr << "Failed parsing" << endl;
  }
  return 0;
}
