# rabbitmq-cpp-example

Todo, what is this app and why does it exist?

Docker build based on https://github.com/robotdad/findfaces
I use a multi-stage container build to build the source, run the tests and prepare a runtime container that is much smaller

## Using the multistage container
It can be as simple as 

    docker build -t rabbitmqcppexample/run .

This does result in a large intermdiate image that is unnamed. You may wish to reuse that image for additional development purposes, e.g. for preparing a container for use with VS. If so simply target the build stage and name it.

    docker build --target build -t rabbitmqcppexample/build .

Then that image will be cached and used when you prepare the run image.

    docker build -t rabbitmqcppexample/run .

To run the service:

    docker run -d --rm  -p 8080:8080 --name rabbitmqcppexample rabbitmqcppexample/run

This will start the container detached and will delete it when it is stopped (but not on windows, you need to stop it manually).

Attach to the container while running to watch process output.

    docker exec -it rabbitmqcppexample

Or attach with an interactive session.

    docker exec -it rabbitmqcppexample /bin/bash

Stop the container

    docker stop rabbitmqcppexample

## Service usage

Todo, service (?). Make this do something