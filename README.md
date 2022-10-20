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

## How to manually send a specific HTTP request
###### <p align="right">Next: [How to perform a stress test](#how-to-perform-a-stress-test)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
"Text for How to manually send a specific HTTP request"
</br></br></br>

### Curl
"Text for Curl"
</br></br></br>

### Netcat
"Text for Netcat"
</br></br></br>

### Postman
"Text for Postman"
</br></br></br>

## How to perform a stress test
###### <p align="right">Next: [Automated tester](#automated-tester)&emsp;Previous: [How to manually send a specific HTTP request](#how-to-manually-send-a-specific-http-request)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
"Text for How to perform a stress test"
</br></br></br>

### How to install siege
"Text for How to install siege"
</br></br></br>

#### Install brew
"Text for Install brew"
</br></br></br>

#### Install siege
"Text for Install siege"
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
</br></br></br>

### Setup
Clone the "make-42-webserv-great-again" repository into the root directory of your "webserv" repository.</br>
</br>
"default error page" = error_page
"client body size" = max_body_size
"directory listing" = autoindex</br>
"default file to answer if the request is a directory" = index_page (only the file name which then will be searched in the requested directory)</br>
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
</br></br></br>

### How to launch
Start your server with the configuration described in [Setup](#setup) and use ```make run``` in the command line from the root of the "make-42-webserv-great-again" repository.
</br></br></br>

### How to customize
"Text for How to customize"

#### Modify custom tests
To add, remove or change custom tests, edit the file *1_custom.cpp* within the root of the "make-42-webserv-great-again" repository.

#### Modify GET request tests
To add, remove or change GET request tests, edit the file *2_get.cpp* within the root of the "make-42-webserv-great-again" repository.

#### Modify POST request tests
To add, remove or change POST request tests, edit the file *3_post.cpp* within the root of the "make-42-webserv-great-again" repository.

#### Modify DELETE request tests
To add, remove or change DELETE request tests, edit the file *4_delete.cpp* within the root of the "make-42-webserv-great-again" repository.
</br></br></br>






## manual testing

### via terminal command line

#### curl

curl -X POST -H "Content-Type: plain/text" --data "BODY IS HERE write something shorter or longer than body limit" http://localhost:8080/new_file.txt

curl --resolve webserv.com:80:127.0.0.1 http://webserv.com/
(Port 80 is deafault and therefore not needed)

curl --resolve www.webserv.com:8080:127.0.0.1 http://www.webserv.com:8080


#### nc

echo "GET / HTTP/1.1\r\nHost: webserv\r\n\r\n" | nc localhost 8080

### using postman

## siege

siege -b http://localhost:8080/empty.html

### install brew

https://brew.sh/

(https://42born2code.slack.com/archives/C024QR1HT62/p1645537433618059)
if you wanna install brew in goinfre instead of your home drive (because it takes a lot of storage, even more if you install some tools) you can use this command:
rm -rf $HOME/.brew && rm -rf $HOME/goinfre/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew && echo 'export PATH=$HOME/goinfre/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
this command will also remove your current brew packages if you just wanna move it to goinfre you can use this command:
mv $HOME/.brew $HOME/goinfre/.brew && echo 'export PATH=$HOME/goinfre/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
the second one is not tested.
After installing always restart your terminal and run
brew --version
which brew
the second one should show something like this:
/Users/jsiller/goinfre/.brew/bin/brew
with 'jsiller' being replaced by your username

### install siege

brew install siege

If you get _"Error: Xcode alone is not sufficient on Catalina."_ install the xcode Command Line Tools with ```xcode-select --install```. This will open the following installation window:

<img width="453" alt="screenshot" src="https://user-images.githubusercontent.com/80413516/195597554-70cfcfbd-858b-4394-8c5f-7a210feec5ff.png">

Click on install -> aggree -> done and then use ```brew install siege``` again.

