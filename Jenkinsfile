/*
 * h5cc_test Jenkinsfile
 */

def failure_function(exception_obj, failureMessage) {
    def toEmails = [[$class: 'DevelopersRecipientProvider']]
    emailext body: '${DEFAULT_CONTENT}\n\"' + failureMessage + '\"\n\nCheck console output at $BUILD_URL to view the results.', recipientProviders: toEmails, subject: '${DEFAULT_SUBJECT}'
    throw exception_obj
}

node ("cluster") {

    try {
        stage("Checkout projects") {
            checkout scm
        }
    } catch (e) {
        failure_function(e, 'Checkout failed')
    }

    dir("build") {
        try {
            stage("Build") {
                sh 'rm -rf ./*'
                sh """module load gcc/4.9.2
                    module load hdf5/1.8.15p1
                    module load cmake/3.7.2
                    HDF5_ROOT=/mnt/lustre/apps/hdf5/1.8.15p1-shared cmake -Dtest_h5cc=OFF ../source
                    make VERBOSE=1"""
            }
        } catch (e) {
            failure_function(e, 'CMake or build failed')
        }

 
    }
}
