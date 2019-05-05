#!/usr/bin/env bash

function test:run() {
    local test_set=$1
    pushd ./build/
    cmake -DTESTING="${test_set}" -Wno-dev .. #&>/dev/null
    make #&>/dev/null
    ../bin/test
    popd
}



#test:run "RouteModel"
#test:run "RMNodeClass"
#test:run "RMSNodes"
test:run "NodeDist"
