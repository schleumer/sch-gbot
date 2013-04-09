#include <unistd.h>
#include <stdio.h>
#include <curl/curl.h>
#include <pthread.h>
#include <sstream>
#include <iostream>

using namespace std;

size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {
    std::ostringstream *stream = (std::ostringstream*)userdata;
    size_t count = size * nmemb;
    stream->write(ptr, count);
    return count;
}

void * request( void * arg ){
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        std::stringstream stream;
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
        /* example.com is redirected, so we tell libcurl to follow redirection */ 
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);
        /* Perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);
        /* Check for errors */ 
        if(res != CURLE_OK) fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        /* always cleanup */ 
        curl_easy_cleanup(curl);
        //std::string output = stream.get();
        //printf(output.c_str());
        std::cout << "Full shit" << std::endl;
    }
}

int main(int argc, char *argv[]){
    int thread_num = 100;
    pthread_t ts[thread_num];
    for(int c = 0; c < thread_num; c++){
        pthread_create (&ts[c], NULL, request, NULL);
    }
    while(true){
        std::cout << "Main shit" << std::endl;
        sleep(0.1); 
    }
    return 0;
}
