const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <title>ESP32 MAX7219 LED Matrix 32x8 Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Helvetica, sans-serif;}
    h1 {font-size: 1.5rem; color:#2980b9;}

    .div_Form {
      margin: auto;
      width: 90%;
      border:1px solid #D8D8D8;
      border-radius: 10px;
      background-color: #f2f2f2;
      padding: 10px 10px;
    }
    
    .div_Form_Input {display: table; margin: 0px; padding: 0px; box-sizing: border-box;}
    .div_Input_Text {display: table-cell; width: 100%;}
    .div_Input_Text > input {width:99.5%; margin-left: 0px; padding-left: 2px; box-sizing: border-box;}

    .buttonSubmit {
      display: inline-block;
      padding: 5px 25px;
      font-size: 13px;
      cursor: pointer;
      text-align: center;
      text-decoration: none;
      outline: none;
      color: #fff;
      background-color: #4CAF50;
      border: none;
      border-radius: 8px;
      box-shadow: 0 3px #999;
    }
    .buttonSubmit:hover {background-color: #3e8e41}
    .buttonSubmit:active {background-color: #3e8e41; box-shadow: 0 1px #666; transform: translateY(2px);}
    .buttonSubmit:disabled {background-color: #666; box-shadow: 0 1px #666; transform: translateY(2px);}
  </style>
  
  <body>
    <div style="text-align: center;">
      <h1>ESP32 MAX7219 LED Matrix 32x8 Web Server</h1>
    </div>

    <div class="div_Form">
      <form>
        <label for="Keys_TXT">Key :</label>
        <input type="password" id="Keys_TXT" name="Keys_TXT" maxlength="20" placeholder="Enter key here..." />
        
        <br>
        
        <hr style="border: 1px solid #e6e6e6;">
        
        <label>Text 1 :</label>
        <div class="div_Form_Input" style="width: 100%;">
          <div class="div_Input_Text">
            <input type="text" id="TXT_1" name="TXT_1" maxlength="100" placeholder="Enter text here...(Max 100 characters)" />
          </div>
          <button type="button" onclick="clear_TXT(1)">X</button>
        </div>
        
        <br>
        
        <label>Text 2 :</label>
        <div class="div_Form_Input" style="width: 100%;">
          <div class="div_Input_Text">
            <input type="text" id="TXT_2" name="TXT_2" maxlength="100" placeholder="Enter text here...(Max 100 characters)" />
          </div>
          <button type="button" onclick="clear_TXT(2)">X</button>
        </div>
        
        <br>
        
        <label>Text 3 :</label>
        <div class="div_Form_Input" style="width: 100%;">
          <div class="div_Input_Text">
            <input type="text" id="TXT_3" name="TXT_3" maxlength="100" placeholder="Enter text here...(Max 100 characters)" />
          </div>
          <button type="button" onclick="clear_TXT(3)">X</button>
        </div>
        
        <br>
        
        <label>Text 4 :</label>
        <div class="div_Form_Input" style="width: 100%;">
          <div class="div_Input_Text">
            <input type="text" id="TXT_4" name="TXT_4" maxlength="100" placeholder="Enter text here...(Max 100 characters)" />
          </div>
          <button type="button" onclick="clear_TXT(4)">X</button>
        </div>
        
        <hr style="border: 1px solid #e6e6e6;">
        
        <button type="button" class="buttonSubmit" id="BTN_Submit" onclick="BTN_Submit_Click()">Submit</button>
        <button type="button" class="buttonSubmit" id="BTN_Getting_Texts" onclick="BTN_Getting_Texts_Click()">Getting Texts</button>
      </form>
    </div>

    <script>
      //________________________________________________________________________________ function clear_TXT(x)
      // Function to clear the text input field.
      function clear_TXT(x) {
        if (x == 1) document.getElementById("TXT_1").value = "";
        if (x == 2) document.getElementById("TXT_2").value = "";
        if (x == 3) document.getElementById("TXT_3").value = "";
        if (x == 4) document.getElementById("TXT_4").value = "";
      }
      //________________________________________________________________________________

      //________________________________________________________________________________ function BTN_Submit_Click()
      // Function to set the text to be displayed on the LED Matrix.
      function BTN_Submit_Click() {
        var key_TXT = document.getElementById("Keys_TXT").value;

        if (key_TXT == "") {
          alert("Error ! \rThe key cannot be empty.");
          return;
        }
        
        var TB_1 = document.getElementById("TXT_1").value;
        var TB_2 = document.getElementById("TXT_2").value;
        var TB_3 = document.getElementById("TXT_3").value;
        var TB_4 = document.getElementById("TXT_4").value;

        var msg;
        msg = "key=" + key_TXT;
        msg += "&sta=set";
        msg += "&Text1=" + TB_1;
        msg += "&Text2=" + TB_2;
        msg += "&Text3=" + TB_3;
        msg += "&Text4=" + TB_4;
        
        Send("set", msg);
      }
      //________________________________________________________________________________

      //________________________________________________________________________________ function BTN_Getting_Texts_Click()
      // Function to get the text displayed on the LED Matrix.
      function BTN_Getting_Texts_Click() {
        var key_TXT = document.getElementById("Keys_TXT").value;

        if (key_TXT == "") {
          alert("Error ! \rThe key cannot be empty.");
          return;
        }
        
        var msg;
        msg = "key=" + key_TXT;
        msg += "&sta=get";
        
        Send("get", msg);
      }
      //________________________________________________________________________________

      //________________________________________________________________________________ function apply_the_Received_Texts(texts)
      // Function to display text displayed in the LED Matrix in the text input field.
      function apply_the_Received_Texts(texts) {
        const myArray_Getting_Texts = texts.split("|");
        
        document.getElementById("TXT_1").value = myArray_Getting_Texts[0];
        document.getElementById("TXT_2").value = myArray_Getting_Texts[1];
        document.getElementById("TXT_3").value = myArray_Getting_Texts[2];
        document.getElementById("TXT_4").value = myArray_Getting_Texts[3];
      }
      //________________________________________________________________________________

      //________________________________________________________________________________ function Send(sta, msg)
      function Send(sta, msg) {
        if (window.XMLHttpRequest) {
          // code for IE7+, Firefox, Chrome, Opera, Safari
          xmlhttp = new XMLHttpRequest();
        } else {
          // code for IE6, IE5
          xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
        xmlhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            if (this.responseText == "+ERR") {
              alert("Error !\rWrong Key !\rPlease enter the correct key.");
              return;
            }
            
            if (sta == "get") {
              apply_the_Received_Texts(this.responseText);
            }
          }
        }
        xmlhttp.open("GET", "settings?" + msg, true);
        xmlhttp.send();
      }
      //________________________________________________________________________________
    </script>
  </body>
</html>
)=====";