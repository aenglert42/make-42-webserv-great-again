# make-42-webserv-great-again
A guide on how to manually test your "42 Coding School" project "webserv" (October 2022) and a beta version of an automated tester.
</br>

## Table of contents
* [How to manually send a specific HTTP request](#how-to-manually-send-a-specific-http-request)
  * [Curl](#curl)
  * [Netcat](#netcat)
  * [Postman](#postman)
* [How to perform a stress test](#how-to-perform-a-stress-test)
  * [How to install siege](#how-to-install-siege)
    * [Install brew](#install-brew)
    * [Install siege](#install-siege)
* [Automated tester](#automated-tester)
  * [Setup](#setup)
  * [How to launch](#how-to-launch)
  * [How to customize](#how-to-customize)
</br>

## How to manually send a specific HTTP request
###### <p align="right">Next: [How to perform a stress test](#how-to-perform-a-stress-test)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
There are many tools taht you can use to send specific HTTp requests to test how your server responds. To name some of them there are curl, netcat and postman which are all available on the schools iMacs.</br>
</br>
### Curl
Curl is a command-line utility for transferring data from or to a server.</br>
</br>
The -X option lets you define the HTTP request method (by default it is GET)</br>
The -H option lets you add, replace or remove request header fields (curl adds some by default)</br>
The --data option lets you add a request body.</br>
The --resolve option allows you to internally redirect the requests for a host to an IP address. You can use this to be able to send requests to hosts other than 127.0.0.1 or localhost.

Here are a few examples of how to use it:</br>
</br>
```curl -X POST -H "Content-Type: plain/text" --data "request body text" http://localhost:8080/new_file.txt```</br>
</br>
```curl --resolve www.webserv.com:8080:127.0.0.1 http://www.webserv.com:8080/```</br>
</br>
```curl --resolve webserv.com:80:127.0.0.1 http://webserv.com/index.html``` (here port 80 is not needed, becuse it is the default port for HTTP)</br>
</br>

### Netcat
Netcat is a computer networking utility for reading from and writing to network connections using TCP or UDP. You can use it to send a freely written HTTP request to your server. This is nice beacuse this way you could also send invalid requests. An easy way of using netcat is to echo your custom request and pipe it into netcat as follows:</br>
</br>
```echo "GET / HTTP/1.1\r\nHost: webserv\r\n\r\n" | nc localhost 8080```</br>
</br>
### Postman
Postman is an API platform for building and using APIs. You can use it to send HTTP requests to your server. Download it to to your school iMac via the "Managed Software Center".
</br></br></br>

## How to perform a stress test
###### <p align="right">Next: [Automated tester](#automated-tester)&emsp;Previous: [How to manually send a specific HTTP request](#how-to-manually-send-a-specific-http-request)&emsp;&emsp;[[Contents](#table-of-contents)]</p>

Siege is a HTTP load test and benchmark utility and can be used to stress a web server. If you use it with the -b option it will send the request without delays in between and until you exit it (e.g. with ctrl+c). It will then show a summary of the test where you can see the availability. The evaluation sheet asks for an availibility > 99.5%.</br>
</br>
For example the command:</br>
</br>
```siege -b http://localhost:8080/empty.html```</br>
</br>
could give you an output similar to this one:</br>

<img width="448" alt="image" src="https://user-images.githubusercontent.com/80413516/197219605-cd922269-050c-46e2-8778-b16dcb974a4f.png">

### How to install siege
You can install siege on the school iMacs by using brew, as described below.
</br>

#### Install brew

The following command installs brew and adds the path to its binary to .zshrc, so it can be used without the path. If you want to use it in bash, replace "zsh" with "bash".

```rm -rf $HOME/.brew && git clone --depth=1 <https://github.com/Homebrew/brew> $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update```

#### Install siege
To install siege you need [brew](#install-brew). Use the command ```brew install siege```. If you get _"Error: Xcode alone is not sufficient on Catalina."_ install the xcode Command Line Tools with ```xcode-select --install```. This will open the following installation window:

<img width="453" alt="screenshot" src="https://user-images.githubusercontent.com/80413516/195597554-70cfcfbd-858b-4394-8c5f-7a210feec5ff.png">

Click on install -> aggree -> done and then use ```brew install siege``` again.
</br></br></br>

## Automated tester
###### <p align="right">Previous: [How to perform a stress test](#how-to-perform-a-stress-test)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
The automated tester is kind of a beta version (private tester made public) and lacks a lot of testing and errorhandling, but I guess it can be usefull anyway. Because some tests depend on the implementation of the server it is also possible that the behaviour of your server might me correct although the tester marks it as wrong or vice versa.</br>
</br>
The tester will send different HTTP requests (test cases) to your server and compare the response it revieves with the expected outcome string. There are three stages of comparison. As soon as a comparison for a test case succeeds, no further comparisons for this test case will be made.
In the first stage the tester checks for an exact match between the response body and the expected result. On success the tester shows "OK".
If it is not an exact match the expected result string gets interpreted as status code (if possible) and gets checked against the response's status code. On success the tester shows "OK status code: " followed by the status code.
For the last stage of comparison the response body is checked for an occurrence of the "expected outcome string". If it is found the tester shows "OK found: " followed by the found string. This comparison is very unexact, therefore the "expected output string" should be as special as possible to lower the change of false positives.
If none of the comparisons succeeds, the tester will show "KO" followed by the received response.

The output looks like this:</br>
<img width="397" alt="image" src="https://user-images.githubusercontent.com/80413516/197232070-93e01c52-14ea-40ec-b971-213a4424d69b.png">
</br>The blue text shows the file and line number of the test case. You can press the command key and left-click on it to jump there.

On each run the tester will create the following directory structure within make-42-webserv-great-again/server/ and delete it afterwards:</br>
```
root/
├── dir/
│   ├── %file
│   ├── custom/
│   ├── index/
│   │   ├── custom/
│   │   │   └── custom.html
│   │   ├── index.html
│   │   └── no/
│   │       ├── autoindex/
│   │       ├── no_autoindex/
│   │       └── no_permission_dir/
│   ├── no_permission_dir/
│   │   ├── file
│   │   └── file.cgi
│   ├── one/
│   │   ├── custom.html
│   │   └── two/
│   │       └── index.html
│   ├── permission_dir/
│   │   ├── .cgi
│   │   ├── file
│   │   ├── file.cgi
│   │   └── no_permission_file
│   └── uploads/
│       ├── file.cgi
│       ├── no_permission_dir/
│       │   └── file
│       ├── no_permission_file
│       └── no_permission_file.cgi
├── index.html
├── server1/
│   ├── custom/
│   │   └── custom.html
│   ├── file
│   └── file.cgi
└── server2/
    ├── file
    └── file.cgi
```
</br></br></br>

### Setup
Clone the "make-42-webserv-great-again" repository into the root directory of your "webserv" repository.</br>
</br>
Create a configuration file with the following settings:</br>
</br>
#### &ensp;Virtual Server 0
&emsp;&emsp;__server_name:__ webserv</br>
&emsp;&emsp;__port:__ 80</br>
&emsp;&emsp;__root:__ make-42-webserv-great-again/server/root/</br>
&emsp;&emsp;__max_body_size:__ 100</br>
&emsp;&emsp;__autoindex:__ false</br>
&emsp;&emsp;__index_page:__ index.html</br>
&emsp;&emsp;__cgi .cgi:__ should be executed using the executable	"make-42-webserv-great-again/server/cgi_bin/cgi".</br>
</br>
&emsp;&emsp;__route /route/__</br>
&emsp;&emsp;&emsp;allowed methods: GET</br>
&emsp;&emsp;&emsp;routed to: make-42-webserv-great-again/server/root/dir/</br>
</br>
&emsp;&emsp;__route /route/one/__</br>
&emsp;&emsp;&emsp;allowed methods: GET</br>
&emsp;&emsp;&emsp;index_page: custom.html</br>
&emsp;&emsp;&emsp;routed to: make-42-webserv-great-again/server/root/dir/one</br>
</br>
&emsp;&emsp;__route /route/one/two/__</br>
&emsp;&emsp;&emsp;allowed methods: GET</br>
&emsp;&emsp;&emsp;index_page: index.html</br>
&emsp;&emsp;&emsp;routed to: make-42-webserv-great-again/server/root/dir/index/</br>
</br>
&emsp;&emsp;__route /uploads/__</br>
&emsp;&emsp;&emsp;allowed methods: GET, POST, DELETE</br>
&emsp;&emsp;&emsp;routed to: make-42-webserv-great-again/server/root/dir/uploads/</br>
</br>
&emsp;&emsp;__route /index/__</br>
&emsp;&emsp;&emsp;allowed methods: GET</br>
&emsp;&emsp;&emsp;routed to: make-42-webserv-great-again/server/root/dir/index/</br>
</br>
&emsp;&emsp;__route /index/no/autoindex/__</br>
&emsp;&emsp;&emsp;allowed methods: GET</br>
&emsp;&emsp;&emsp;autoindex: true</br>
&emsp;&emsp;&emsp;routed to: make-42-webserv-great-again/server/root/dir/index/no/autoindex/</br>
</br>
&emsp;&emsp;__route /index/no/no_autoindex/__</br>
&emsp;&emsp;&emsp;allowed methods: GET</br>
&emsp;&emsp;&emsp;autoindex: false</br>
&emsp;&emsp;&emsp;routed to: make-42-webserv-great-again/server/root/dir/index/no/no_autoindex/</br>
</br>
&emsp;&emsp;__route /index/custom/__</br>
&emsp;&emsp;&emsp;allowed methods: GET</br>
&emsp;&emsp;&emsp;index_page: custom.html</br>
&emsp;&emsp;&emsp;routed to: make-42-webserv-great-again/server/root/dir/index/custom/</br>
</br>
#### &ensp;Virtual Server 1
&emsp;&emsp;__server_name:__ server1</br>
&emsp;&emsp;__port:__ 6000</br>
&emsp;&emsp;__root:__ make-42-webserv-great-again/server/root/server1/</br>
&emsp;&emsp;__error_page 404:__ make-42-webserv-great-again/server/root/server1/custom/custom.html</br>
&emsp;&emsp;__cgi .cgi:__ should be executed using the executable	"make-42-webserv-great-again/server/cgi_bin/no_permission_cgi".</br>

#### &ensp;Virtual Server 2
&emsp;&emsp;__server_name:__ server2</br>
&emsp;&emsp;__port:__ 8080, 8081</br>
&emsp;&emsp;__root:__ make-42-webserv-great-again/server/root/server2/</br>
&emsp;&emsp;__cgi .cgi:__ should be executed using the executable	"doesntexist".</br>
</br>
&emsp;&emsp;__route /__</br>
&emsp;&emsp;&emsp;allowed methods: none</br>
&emsp;&emsp;&emsp;autoindex: false</br>
&emsp;&emsp;__route /route/__</br>
&emsp;&emsp;&emsp;allowed methods: GET POST</br>
</br>
Relation of subject expression to the used keywords:</br>
</br>
"default error page" = error_page</br>
"client body size" = max_body_size</br>
"directory listing" = autoindex (true / false)</br>
"default file to answer if the request is a directory" = index_page (the name of the file)</br>
</br></br></br>

### How to launch
Start your server with the configuration described in [Setup](#setup) and use ```make run``` in the command line from the root of the "make-42-webserv-great-again" repository.
</br></br></br>

### How to customize
To add, remove or change test cases, edit the corresponding file within the root of the "make-42-webserv-great-again" repository, as described below. To add, remove or change the known host:port combinations for the tester, edit the file *0_hosts.cpp*.</br>

Usage: ```add_host("uri-host", "port");```</br>

#### Modify custom tests
Edit the file *1_custom.cpp* as follows: ```custom_test("HTTP request", "expected resonse body or status code", FILE_LINE);```</br>

The default port for the custom requests is port 80. Make sure your server is listening on it, or change it by edit ```uint16_t g_port_for_custom_requests = 80;```</br>

#### Modify GET request tests
Edit the file *2_get.cpp* as follows: ```GET_test("url", "expected resonse body or status code", FILE_LINE);```</br>

#### Modify POST request tests
Edit the file *3_post.cpp* as follows: ```POST_test("url", "expected resonse body or status code", FILE_LINE);```</br>

#### Modify DELETE request tests
Edit the file *4_delete.cpp* as follows: ```DELETE_test("url", "expected resonse body or status code", FILE_LINE);```</br>
</br></br></br>
