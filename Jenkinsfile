// pipeline {
//   agent any

//   stages {
//     stage('Check CMake') {
//       steps {
//         sh 'cmake --version'
//       }
//     }
//     stage('Checkout') {
//       steps {
//         checkout scm
//       }
//     }

//     stage('Build') {
//       steps {
//         sh 'cmake -B build -S .'
//         sh 'cmake --build build'
//       }
//     }

//     stage('Unit Tests') {
//       steps {
//         sh 'cd build && ctest'
//       }
//     }
//   }
// }



pipeline {
  agent any

  tools {
        // Define the CMake installation
        cmake 'cmake'
    }

  stages {
  //    stage('Check CMake') {
  //     steps {
  //       sh 'cmake --version'
  //     }
  //   }
    stage('Configure') {
      steps {
          // Install CMake using the 'tool' step
                tool name: 'cmake', type: 'hudson.plugins.cmake.CmakeToolInstallation'

        // dir('build') {
        //   cmake(
        //     installation: 'InSearchPath'
        //   )
        //   sh 'cmake .'
        // }
      }
    }
    stage('Build') {
      steps {
        dir('build') {
          sh 'cmake --build .'
        }
      }
    }  
    stage('Test') {
      steps {
        dir('build') {
          sh 'ctest -C checkin --output-junit unittest.xml'
        }
      }
    }
  }
  post {
    always {
      // Archive the CTest xml output
      archiveArtifacts (
        artifacts: 'build/*.xml',
        fingerprint: true
      )

      // Process the CTest xml output with the xUnit plugin
      xunit (
        testTimeMargin: '3000',
        thresholdMode: 1,
        thresholds: [
          skipped(failureThreshold: '0'),
          failed(failureThreshold: '0')
        ],
      tools: [CTest(
          pattern: 'build/*.xml',
          deleteOutputFiles: true,
          failIfNotNew: false,
          skipNoTestFiles: true,
          stopProcessingIfError: true
        )]
      )

      // Clear the source and build dirs before next run
      deleteDir()
    }
  }
}