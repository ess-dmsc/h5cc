/*
 * h5cc_test Jenkinsfile
 */

node {

    stage("Checkout projects") {
        checkout scm
    }

    dir("build") {
        stage("Run CMake") {
            sh 'rm -rf ./*'
            sh "HDF5_ROOT=/opt/dm_group/hdf5 \
                cmake ../code/source"
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
