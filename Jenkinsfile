/*
 * h5cc_test Jenkinsfile
 */

def failure_function(exception_obj, failureMessage) {
    def toEmails = [[$class: 'DevelopersRecipientProvider']]
    emailext body: '${DEFAULT_CONTENT}\n\"' + failureMessage + '\"\n\nCheck console output at $BUILD_URL to view the results.', recipientProviders: toEmails, subject: '${DEFAULT_SUBJECT}'
    throw exception_obj
}

node ("boost") {
    try {
        stage("Checkout projects") {
            checkout scm
        }
    } catch (e) {
        failure_function(e, 'Checkout failed')
    }

    dir("build") {
        try {
            stage("Run CMake") {
                sh 'rm -rf ./*'
                sh '/opt/cmake/cmake-3.7.1-Linux-x86_64/bin/cmake --version'
                sh "HDF5_ROOT=$HDF5_ROOT \
                     CMAKE_PREFIX_PATH=$HDF5_ROOT \
                     /opt/cmake/cmake-3.7.1-Linux-x86_64/bin/cmake -DTESTS=1 ../source"
            }
        } catch (e) {
            failure_function(e, 'CMake failed')
        }
        
        try {
            stage("Build project") {
                sh "make VERBOSE=1"
            }
        } catch (e) {
            failure_function(e, 'Build failed')
        }

        try {
            stage("Run test") {
                sh "./test/h5cc_test --gtest_output=xml:LogTests.xml"
                junit '*Tests.xml'
            }
        } catch (e) {
            junit '*Tests.xml'
            failure_function(e, 'Tests failed')
        }
 
    }
}
