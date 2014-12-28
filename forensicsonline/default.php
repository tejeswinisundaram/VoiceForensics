<?php
//
//===============================================================
//VoiceForensics
//https://github.com/utkarshp/VoiceForensics
//===============================================================
//Copyright 2014 VoiceForensics
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
?>


<!DOCTYPE html>
<html>
<head>
<title>  </title>
<link rel="stylesheet" type="textarea/css" href="s.css">
<title>  </title>
<link rel="stylesheet" type="textarea/css" href="style.css">
</head>

<body>
<div class="top" name="global-nav-inner">
 <div class="top-c" name="top-c" >
<H1> Audio Forensics </H1>
 </div>
 </div>
<div class="bod">

<div class="body">
    <div class="line0">
    <H3><center>Do you wish to know how your buddy would look by his/her voice?<br/>
    <br/>
     Do you wish to know your  physical features based on your voice ?<br/><br/>
Simply upload an audio clip to find out.<br/><br/>Enjoy! </center></H3>
  
    </div>
    <div class="line1"align="center">
     Select a file to upload: <br /><br />
     <form action="form_uploader.php" method="post" enctype="multipart/form-data">
        <input type="file" name="file" size="50" class="button1" /> <br />
        <br/>
        <input type="submit"  name='submit' value="Upload File" class="button1" src="file_uploader.php" />
        <br/>
        <br/>
        <br/>
        </form>
    </div>
    <div class="line3">
        <?php
        $file = fopen("file1.csv","r");
        while(! feof($file))
          {
          print_r(fgetcsv($file));
          }

        fclose($file);?>
    Sex: <textarea class="textarea1" name="sex" readonly="true"></textarea>
    <br/>
    Height:<textarea class="textarea1" name="height" readonly="true"></textarea>
    <br/>
    Weight:<textarea class="textarea1" weight="weight" readonly="true"></textarea>
    <br/> 
    BMI:<textarea class="textarea1" name="bmi" readonly="true" ></textarea>
    <br/>
    Waist Size:<textarea class="textarea1" name="waist" readonly="true"></textarea>
    <br/>
    </div>
</div>

</div>
<footer>
Copyright © IPTSE - NITK CMU Winter School 2014.
</footer>
</div>
</body>

</html>