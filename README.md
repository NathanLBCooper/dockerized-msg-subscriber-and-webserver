# rabbitmq-cpp-example

**I'm using Docker containers to create a reproducible build environment for a C++ project**. I'm using a multi-stage container to build the source and run the tests. I'm then creating a runtime container that is much smaller. 

Based on a series on devblogs.microsoft.com:
- [Using multi-stage containers for C++ development](https://devblogs.microsoft.com/cppblog/using-multi-stage-containers-for-c-development/)
- [Using VS Code for C++ development with containers](https://devblogs.microsoft.com/cppblog/using-vs-code-for-c-development-with-containers/)
- [robotdad/findfaces](https://github.com/robotdad/findfaces)

The project itself talks to the world via [RabbitMQ](https://github.com/alanxz/rabbitmq-c) and a [Restinio](https://github.com/Stiffstream/restinio) web server. I imagine it could be given work, the sort of work you want done on C++, by other services.

***NOTE**: I keep this repository in *C:/PersonalSource/*, which turns up in the configurations I provide. If your repository is elsewhere, change this when you see it.*

## Using the multistage container

Create the build image

    docker build --target build -t rabbitmqcppexample/build .

Which will be cached and used to prepare the run image.

    docker build -t rabbitmqcppexample/run .

Then run the service

    docker run -d --rm  -p 8080:8080 --name rabbitmqcppexample rabbitmqcppexample/run

When you're done, stop the container

    docker stop rabbitmqcppexample
    
*[See Docker comand line docs](https://docs.docker.com/engine/reference/commandline/docker/)*

## Service usage

    http://localhost:8080/health

## Debugging on VS Code

#### Create container:

You need to create a development only build container with a few more things we need for debugging

    docker build -t rabbitmqcppexample/vs -f Dockerfile.vs .

Then run that

    docker run -d -p 12345:22 -p 8080:8080 --security-opt seccomp:unconfined -v c:/PersonalSource/rabbitmq-cpp-example/src:/source --name rabbitmqcppexamplevscode rabbitmqcppexample/vs

#### Build C++ in container:

Create this task in your VSCode project (put it in your *.vscode/tasks.json*) and run it:

	{
		"version": "2.0.0",
		"tasks": [
			{
				"label": "build",
				"type": "shell",
				"command": "ssh",
				"args": [
					"root@localhost",
					"-p",
					"12345",
					"/source/build.sh"
				],
				"problemMatcher": [
					"$gcc"
				]
			}
		]
	}
    
#### Debugging C++ in container:
    
Create this launch configuration (put it in your *.vscode/launch.json*)
    
    	{
		"version": "0.2.0",
		"configurations": [
			{
				"name": "C/C++: (gdb) Pipe Launch",
				"type": "cppdbg",
				"request": "launch",
				"program": "/source/output/rabbitmqcppexample",
				"args": [],
				"stopAtEntry": true,
				"cwd": "/src/out",          
				"pipeTransport": {
					"debuggerPath": "/usr/bin/gdb",
					"pipeProgram": "C:/Windows/system32/OpenSSH/ssh.exe",
					"pipeArgs": [
						"root@localhost",
						"-p",
						"12345"
					],
					"pipeCwd": ""
				},
				"sourceFileMap": {
					"/source": "C:/PersonalSource/rabbitmq-cpp-example/src"
				}
			},
		]
	}

#### IntelliSense for C++ with a container:

You need to get the headers on your local machine. Create a directory where you want to put your headers on your local machine. 

If your container is running your can use `scp` to do this. Get the headers and the headers from vcpkg.

    scp -r -P 12345 root@localhost:/usr/include .
    scp -r -P 12345 root@localhost:/tmp/vcpkg/installed/x64-linux-musl/include .
    
Alternatively, you can get them from Docker directly, whether on not the container is running.
   
    docker cp -L rabbitmqcppexamplevscode:/usr/include .
   
Now configure your Intellisense to pickup these headers.

I used *C:/PersonalSource/rabbitmq-cpp-example/headers* as my header location. Here is my *c_cpp_properties.json*:

	{
		"configurations": [
			{
				"name": "Win32",
				"includePath": [
					"${workspaceFolder}/**"
				],
				"defines": [
					"_DEBUG",
					"UNICODE",
					"_UNICODE"
				],
				"windowsSdkVersion": "10.0.17763.0",
				"compilerPath": "C://Ruby24-x64//msys64//mingw64//bin//gcc.exe",
				"cStandard": "c11",
				"cppStandard": "c++17",
				"intelliSenseMode": "gcc-x64",
				"browse": {
					"path": [
						"${workspaceFolder}"
					],
					"limitSymbolsToIncludedHeaders": true,
					"databaseFilename": ""
				}
			}
		],
		"version": 4
	}
    
This is the point where you need a C++ compiler locally (damn!), but I already have one for free with my ruby install.
