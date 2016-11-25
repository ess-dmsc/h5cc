/*
 * h5cc_test Jenkinsfile
 */

node {

    stage("Checkout projects") {
        checkout scm
    }

    stage("Copy artifacts") {
        step([
            $class: "CopyArtifact",
            filter: "usr/",
            fingerprintArtifacts: true,
            projectName: "libhdf5",
            target: "libhdf5"
        ])
    }

    dir("build") {
        stage("Run CMake") {
            sh 'rm -rf ./*'
            sh "HDF5_ROOT=\$(pwd)/../libhdf5/usr \
                cmake ../code"
        }

        stage("Build project") {
            sh "make VERBOSE=1"
        }

        stage("Run test") {
            sh "./h5cc_test"
        }
    }
}
