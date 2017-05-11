/*
 * h5cc_test Jenkinsfile
 */

node ("boost") {

    stage("Checkout projects") {
        checkout scm
    }

    dir("build") {
        stage("Run CMake") {
            sh 'rm -rf ./*'
            sh '/opt/cmake/cmake-3.7.1-Linux-x86_64/bin/cmake --version'
            sh "HDF5_ROOT=$HDF5_ROOT \
                CMAKE_PREFIX_PATH=$HDF5_ROOT \
                /opt/cmake/cmake-3.7.1-Linux-x86_64/bin/cmake -DTESTS=1 ../source"
        }

        stage("Build project") {
            sh "make VERBOSE=1"
        }

        stage("Run test") {
            sh "./h5cc_test --gtest_output=xml:LogTests.xml"
            junit '*Tests.xml'
        }
 
    }
}
