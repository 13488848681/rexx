<?php
// Copyright 2004-present Facebook. All Rights Reserved.

class FacebookFbcodeUnitTestEngine extends ArcanistBaseUnitTestEngine {

  public function run() {
    $result = new ArcanistUnitTestResult();
    $result->setName("jenkins_async_test");
    $result->setResult(ArcanistUnitTestResult::RESULT_POSTPONED);
    return array($result);
  }
}
