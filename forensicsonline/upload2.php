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


<?php
if( $_FILES['file']['name'] != "")
{
   if ((($_FILES["file"]["type"] == "audio/x-wav"))||($_FILES["file"]["type"] == "audio/wav") &&
    ($_FILES["file"]["size"] < 20000000))
   {
     move_uploaded_file ($_FILES['file'] ['tmp_name'], 
       "uploads/{$_FILES['file'] ['name']}") or 
           die( "Could not copy file!");
   
   }
   else{
   header('Location: results.php?error=Wrong File Format');  
   }  
}
else
{
     header('Location: results.php?error=No File Uploaded');  
}
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Audio Forensics - A great tool</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="">
    <meta name="author" content="">

    <!-- Le styles -->
    <link href="bootstrap/css/bootstrap.css" rel="stylesheet">
    <style type="text/css">
      body {
        padding-top: 60px;
        padding-bottom: 40px;
      }
    </style>
    <link href="bootstrap/css/bootstrap-responsive.css" rel="stylesheet">

    <!-- HTML5 shim, for IE6-8 support of HTML5 elements -->
    <!--[if lt IE 9]>
      <script src="../bootstrap/js/html5shiv.js"></script>
    <![endif]-->

    <!-- Fav and touch icons -->

  </head>

  <body>

    <div class="navbar navbar-inverse navbar-fixed-top">
      <div class="navbar-inner">
        <div class="container">
          <button type="button" class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse">
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="brand" href="index.php">Audio Forensics</a>
          <div class="nav-collapse collapse">
            <ul class="nav">
          <li class="active"><a href="upload.php">Upload</a></li>
               <li><a href="about.php">About</a></li>
              <li><a href="contacts.php">Contacts</a></li>
          </div><!--/.nav-collapse -->
        </div>
      </div>
    </div>

    <div class="container">
       <body>
<h2>Uploaded File Info:</h2>
<ul>
<li>Sent file: <?php echo $_FILES['file']['name'];  ?>
<li>File size: <?php echo $_FILES['file']['size'];  ?> bytes
<li>File type: <?php echo $_FILES['file']['type'];  ?>
</ul>

 <div class="hero-unit" align="left">
 <?php
  $file = fopen("file1.csv","r");
  $arr;
        while(! feof($file))
          {
          $arr=(fgetcsv($file));

          }
  echo '<h2>Output</h2>
          <p>
        <br/>
        <strong>Sex:</strong> ';
        echo $arr[0];
        echo '
        <br/>
        <strong> Height:</strong>  ';
        echo $arr[1];
        echo ' 
        <br/>
        <strong> Weight:</strong> ';
        echo $arr[2];
        echo ' 
        <br/> 
        <strong> BMI:</strong>  ';
        echo $arr[3];
        echo '
        <br/>
        <strong> Waist Size:</strong>  ';
        echo $arr[4];
        echo ' 
        <br/>
        </div>
        </p>
        </div>
      </div>';
        fclose($file);?>

</body>
        </div> <!-- /container -->

      <footer>
        <p>&copy;IPTSE - NITK-CMU Winter School 2014</p>
      </footer>

    <!-- Le javascript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="bootstrap/js/jquery.js"></script>
    <script src="bootstrap/js/bootstrap-transition.js"></script>
    <script src="bootstrap/js/bootstrap-alert.js"></script>
    <script src="bootstrap/js/bootstrap-modal.js"></script>
    <script src="bootstrap/js/bootstrap-dropdown.js"></script>
    <script src="bootstrap/js/bootstrap-scrollspy.js"></script>
    <script src="bootstrap/js/bootstrap-tab.js"></script>
    <script src="bootstrap/js/bootstrap-tooltip.js"></script>
    <script src="bootstrap/js/bootstrap-popover.js"></script>
    <script src="bootstrap/js/bootstrap-button.js"></script>
    <script src="bootstrap/js/bootstrap-collapse.js"></script>
    <script src="bootstrap/js/bootstrap-carousel.js"></script>
    <script src="bootstrap/js/bootstrap-typeahead.js"></script>

  </body>
</html>
