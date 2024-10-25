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

int main(int argc, char const *argv[]) {
  string response = rest_get("https://jsonplaceholder.typicode.com/todos/1");
  cout << "Response: " << response << endl;
  return 0;
}
