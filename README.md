# make-42-webserv-great-again
A guide on how to manually test your "42 Coding School" project "webserv" (October 2022) and beta version of an automated tester.
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
"Text for Automated tester"
</br></br></br>

### Setup
"Text for Setup"
</br></br></br>

### How to launch
"Text for How to launch"
</br></br></br>

### How to customize
"Text for How to customize"
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

