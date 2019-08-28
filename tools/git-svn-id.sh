#!/bin/bash

git rev-list --branches HEAD | wc -l | tr -d ' ' | tr -d '\n'
