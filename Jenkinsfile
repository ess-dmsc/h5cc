/*
 * h5cc_test Jenkinsfile
 */

node ("cluster") {

    stage("Checkout projects") {
        checkout scm
    }

    dir("build") {
        stage("Run CMake") {
            sh 'rm -rf ./*'
            sh """module load gcc/4.9.2
                  module load hdf5/1.8.15p1
                  module load cmake/3.7.2
                  cmake -Dtest_h5cc=OFF ../source
                  make VERBOSE=1"""
        }

        stage("Run test") {
            sh "./test/h5cc_test --gtest_output=xml:LogTests.xml"
            junit '*Tests.xml'
        }
 
    }
}
