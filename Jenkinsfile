#!/usr/bin/env groovy

pipeline {
	agent any

	stages {
		stage ('Build') {
			steps {
				sh 'autoreconf -i && ./configure && make'
			}
		}
		stage('Test') {
			steps {
				sh 'make check'
			}
		}
	}
}
