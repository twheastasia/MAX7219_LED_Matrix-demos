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

    select {
      width: 100%;
      padding: 12px 20px;
      margin: 8px 0;
      display: inline-block;
      border: 1px solid #ccc;
      border-radius: 4px;
      box-sizing: border-box;
    }
  </style>
  
  <body>
    <div style="text-align: center;">
      <h1>ESP32 MAX7219 LED Matrix 32x8 Web Server</h1>
    </div>

    <div class="div_Form">
      <form>
        <label for="operation">四则运算:</label>
        <select id="operation" name="operation" multiple>
          <option value="PLUS">PLUS</option>
          <option value="MINUS">MINUS</option>
          <option value="MULTIPLE">MULTIPLE</option>
          <option value="DIVIDE">DIVIDE</option>
        </select>
        
        <br><br>
        
        <label for="range">范围:</label>
        <select id="range" name="range">
          <option value="10">10</option>
          <option value="20">20</option>
          <option value="30">30</option>
          <option value="40">40</option>
          <option value="50">50</option>
          <option value="60">60</option>
          <option value="70">70</option>
          <option value="80">80</option>
          <option value="90">90</option>
          <option value="100">100</option>
        </select>
        
        <br><br>
        
        <button type="button" class="buttonSubmit" id="BTN_Next" onclick="BTN_Next_Click()">下一题</button>
      </form>
    </div>

    <script>
      // Function to handle the next question button click
      function BTN_Next_Click() {
        var selectedOperations = Array.from(document.getElementById("operation").selectedOptions).map(option => option.value).join(",");
        var selectedRange = document.getElementById("range").value;

        var msg = "triggerNext=true&symbol=" + selectedOperations + "&maxValue=" + selectedRange;
        
        Send("configs", msg);
      }

      // Function to send the request
      function Send(endpoint, msg) {
        var xmlhttp;
        if (window.XMLHttpRequest) {
          // code for IE7+, Firefox, Chrome, Opera, Safari
          xmlhttp = new XMLHttpRequest();
        } else {
          // code for IE6, IE5
          xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
        xmlhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
          }
        }
        xmlhttp.open("GET", endpoint + "?" + msg, true);
        xmlhttp.send();
      }
    </script>
  </body>
</html>
)=====";
