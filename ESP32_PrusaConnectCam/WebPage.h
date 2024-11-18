/**
   @file WebPage.h

   @brief Here is saved root WEB page

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   https://codebeautify.org/remove-extra-spaces

   @bug: no know bug
*/

#pragma once

#define MSG_REBOOT_MCU        "Reboot process started, wait several seconds for mcu to boot up. You can close this window now"
#define MSG_SAVE_OK_REBOOT    "Save OK. Please reboot MCU"            ///< WEB app msg save OK
#define MSG_SAVE_OK_WIFI      "Save OK. Connecting to Wi-Fi. Please wait several seconds"
#define MSG_SAVE_OK           "Save cfg OK"                           ///< WEB app msg save OK
#define MSG_SAVE_NOTOK        "Save cfg NOT OK!"                      ///< WEB app msg save NOT OK
#define MSG_SCANNING          "Scanning Wi-Fi networks. Wait 8s..."   ///< WEB app msg Scanning wifi
#define MSG_UPDATE_START      "Start updating"

/* ------------------------------------------------------------------------------------------------------------ */
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html lang="en">
<head>
	<meta name="Prusa ESP32-cam" content="width=device-width, initial-scale=1">
	<link rel="icon" href="/favicon.svg" type="image/svg+xml">

	<link rel="stylesheet" type="text/css" href="styles.css?v=1.0.0">
	<script src="jquery-3.7.0.min.js"></script>
	<script>
		$(document).ready(function () {
			$("a").click(function (e) {
				e.preventDefault();
				var page = $(this).attr("href");
				$("#content").load(page);
				setActive(this);
			});
			$("#content").load("page_config.html", function() {
				var defaultLink = document.querySelector('a[href="page_config.html"]');
				setActive(defaultLink);
			});
		});
	</script>
</head>
<body>
    <nav>
    <img src="esp32_cam.svg" id=logo alt="Logo image" style="margin-left: 10px;" />
      <ul class="top_bar" style="justify-content:flex-start;">
        <li><a class=p5 href="https://forum.prusa3d.com/forum/prusa-connect-prusalink" id="forum-link">Forum</a></li>
		<li><a class=p5 href="https://help.prusa3d.com/guide/esp-camera-for-prusa-connect_390199" id="forum-link">Help</a></li>
      </ul>
      <ul class="top_bar" style="justify-content:flex-end;">
		<li><a class=p4 href="#" onclick="javascript:actionButton('/action_led',true,'')"><div id="light-icon"></div> Light </a></li>
		<li><a class=p4 href="#" onclick="location.reload();"><svg height="25" width="25"><image href="refresh-icon.svg"></svg> Refresh </a></li>
		<li><a class=p4 href="#" onclick="javascript:actionButton('/action_reboot',false,'Reboot process started, wait several seconds for mcu to boot up. You can close this window now.')"><svg height="25" width="25"><image href="reboot-icon.svg"></svg> Reboot </a></li>
      </ul>
    </nav>
	<hr>
	<section class="container">
		<div  class="container_left-half">
			<article>
				<img src="saved-photo.jpg" id="photo"  width="60%" onclick="openImage()"/>
			</article>
		</div>
		<div class="container_right-half">
			<article>
				<p class="p1">Trigger interval: <b><span id="refreshInterval"></span><b>s</p><br><br>
				<button class="btn" onclick="actionButton('/action_capture',true,'')">Refresh Snapshot</button> <br><br>
				<button class="btn" onclick="actionButton('/action_send',false,'Sending snapshot...')">Send snapshot</button><br><br><br>
				<button class="btn" onclick="window.open('saved-photo.jpg')">Download snapshot</button><br><br>
				<button class="btn" onclick="window.open('stream.mjpg')">Start stream</button><br><br>
			</article>
		</div>
	</section>
	<br>
	    <div id="cfg">
			<div id="cfg_bar">
			<div id="links">
				<li><a href="page_config.html">Camera</a></li>
				<li><a href="page_wifi.html">Wi-Fi</a></li>
				<li><a href="page_auth.html">Authentication</a></li>
				<li><a href="page_system.html">System</a></li>
				<li><a href="page_temperature.html">Temperature</a></li>
				</div>
			</div>
		</div>
	<hr>
	<div id="content">
	</div>
	<br><br><br><br>
	<table id=botton><tr>
		<td><p class=p2>Prusa Connect ESP32 cam</p> </td>
		<td><p class=p3>Author</p> <p class=p2>Miroslav Pivovarsky</p> </td>
		<td><a href="license.html" class=p3>Licence</a> | <a href="gtac.html" class=p3>General Terms and Conditions</a> | <a href="privacypolicy.html" class=p3>Privacy Policy</a> | <a href="cookie.html" class=p3>Cookie Preferences</a> </td>
		<td><a href="https://github.com/Prusa-Development/Prusa-Firmware-ESP32-Cam/" id="github-link"><svg height="25"><image href="github-icon.svg"></svg></a></td>
	</tr></table>
</body>
<script src="scripts.js"></script>
<script>
	sliderCheck();
	get_data();
	addClickListener('github-link');
	addClickListener('forum-link');
</script>
</html>
)rawliteral";

/* ------------------------------------------------------------------------------------------------------------ */
const char page_auth_html[] PROGMEM = R"rawliteral(
<style>@import url("styles.css?v=1.0.0");</style>
<script src="jquery-3.7.0.min.js"></script>
<body>
	<center>
		<table>
			<tr><td class=pa3>Set web authentication</td><td></td></tr>
			<tr><td class=pa1 align="right">WEB authentication </td><td><label class="switch"><input type="checkbox" name="basicauth_enable" id="authid" onchange="changeValue(this.checked, 'basicauth_cfg?basicauth_enable=', 'auth')"><span class="checkbox_slider round"></span></label></label> <span class=pa1 id="status_auth"></span></td></tr>
			<tr><td class=pa1 align="right">Username </td><td><input type="text" name="auth_username" id="auth_username"></td></tr>
			<tr><td class=pa1 align="right">Password </td><td><input type="password" name="auth_password" id="auth_password"><span class="toggle-password" onclick="togglePasswordVisibility()"><img id="eye-icon" src="eye.svg" alt="Show Password"></span></td></tr>
			<tr><td class=pa1 align="right">Confirm Password </td><td><input type="password" name="auth_password_confirm" id="auth_password_confirm"><span class="toggle-password" onclick="togglePasswordVisibility()"><img id="eye-icon-confirm" src="eye.svg" alt="Show Password"></span><span id="pass_match"></span></td></tr>
			<tr><td></td><td><button class="btn_save_a" onclick="setAuth( document.getElementById('auth_username').value, document.getElementById('auth_password').value)">Save</button></td></tr>
		</table>
	</center>
</body>
<script src="scripts.js"></script>
<script>
	get_data("auth");
	document.getElementById("auth_password").addEventListener("input", validatePasswords);
    document.getElementById("auth_password_confirm").addEventListener("input", validatePasswords);
    validatePasswords();
</script>
)rawliteral";

/* ------------------------------------------------------------------------------------------------------------ */
const char page_wifi_html[] PROGMEM = R"rawliteral(
<style>@import url("styles.css?v=1.0.0");</style>
<script src="jquery-3.7.0.min.js"></script>
<body>
	<table id="center_tb">
		<tr><td></td><td style="width:40%">
			<p class="w1">Connection status</p>
			<p class="w2">Status: <span id="wifi_network_status"></span></p>
			<p class="w2">SSID: <span id="ssid"></span></p>
			<p class="w2">Signal: <span id="main-wifi-signal" ></span><span id="rssi_percentage"></span>% / <span id="rssi"></span>dBm</p>
			<p class="w2">IP Address: <span id="ip"></span></p>
			<p class="w2">mDNS: http://<span id="mdns"></span>.local</p>
		</td><td></td></tr>
		<tr><td></td><td style="width:40%">
			<br>
			<p class="w1">Available networks</p>
			</td><td></td></tr>
			<tr><td></td><td style="width:40%">
			<table id="wifi_ntw">
				<colgroup>
					<col style="width: 30%;">
					<col style="width: 35%;">
					<col style="width: 15%;">
					<col style="width: 20%;">
				</colgroup>
				<tr>
					<th>Network name (SSID)</th>
					<th>Signal strength (RSSI)</th>
					<th>Channel</th>
					<th>Encryption</th>
				</tr>
			</table>
		</td><td></td></tr>
		<tr><td></td><td style="width:40%" align="right">
			<button class="btn" onclick="scanWifi()">Scan Wi-Fi networks</button>
			<br>
		</td><td></td></tr>
		<tr><td></td><td style="width:40%">
			<br>
			<table>
				<tr><td class="w1">Connect to Wi-Fi network</td></tr>
				<tr><td class="w2"  align="right">Wi-Fi network name (SSID) </td><td><input type="text" name="wifi_ssid" id=wifi_ssid_id ></td></tr>
				<tr><td class="w2"  align="right">Password </td><td><input type="text" name="wifi_pass" id=wifi_pass_id></td></tr>
				<tr><td></td><td align="center"><button class="btn_save_w" onclick="setWifi(document.getElementById('wifi_ssid_id').value, document.getElementById('wifi_pass_id').value)">Save & Connect</button></td></tr>
			</table>
		</td><td></td></tr>
	</table>
	<br>
	<center>
		<button class="btn_collapsible_wifi">Advanced Wi-Fi settings</button>
	</center>
	<div class="content_wifi">
		<br>
		<table id="wificfg_tb">
			<tr><td class="w1">Advanced Wi-Fi settings</td></tr>
			<tr><td class="w2" align="right">Enable service AP </td><td><label class="switch"><input type="checkbox" name="serviceap_enable" id="serviceapid" onchange="changeValue(this.checked, 'set_bool?serviceap_enable=', 'wifi')"><span class="checkbox_slider round"></span></label></label> <span class="w1" id="status_serviceap"></span></td></tr>
			<tr><td style="height: 10px;"></td></tr>
			<tr><td class="w2" align="right">Wi-Fi client IPv4 Method</td><td><label for="loglevel"></label>
				<select class="select" id="ipcfgid" name="ipcfg" onchange="changeValue(this.value, 'set_int?ipcfg=', 'wifi')">
					<option value="0">DHCP</option>
					<option value="1">Manual (static IP)</option>
				</select>
			</td></tr>
			<tr><td class="w2" align="right">IP address</td><td><input type="text" name="net_ip" id=net_ip_id></td></tr>
			<tr><td class="w2" align="right">Subnet mask</td><td><input type="text" name="net_mask" id=net_mask_id></td></tr>
			<tr><td class="w2" align="right">Default gateway</td><td><input type="text" name="net_gw" id=net_gw_id></td></tr>
			<tr><td class="w2" align="right">DNS server</td><td><input type="text" name="net_dns" id=net_dns_id></td></tr>
			<tr><td></td><td align="center"><button class="btn_save_w" onclick="setWifiNet(document.getElementById('net_ip_id').value, document.getElementById('net_mask_id').value, document.getElementById('net_gw_id').value, document.getElementById('net_dns_id').value)">Save</button></td></tr>
		</table>
	</div>
</body>
<script src="scripts.js"></script>
<script>
	setTimeout(function(){GetDataAndPrintTableWiFi();}, 500);
	get_data("wifi");
	setupCollapsibleButtonsWiFi();
</script>
)rawliteral";

/* ------------------------------------------------------------------------------------------------------------ */
const char page_config_html[] PROGMEM = R"rawliteral(
<style>@import url("styles.css?v=1.0.0");</style>
<script src="jquery-3.7.0.min.js"></script>
<body>
	<center><table id="data">
		<tr><td class="ps3">Basic settings</td><td></td></tr>
        <tr><td class="pc1">Connect Token</td><td ><input type="text" name="token" id=tokenid >&nbsp;<button class="btn_save" onclick="changeValue(encodeURIComponent(document.getElementById('tokenid').value), 'set_token?token=', 'config')">Save</button></td></tr>
        <tr><td class="pc1">Fingerprint</td><td class=pc2 id="fingerprint"></td></tr>
		<tr><td class="pc1">Trigger Interval [s]</td><td ><input type="text" name="refresh" id=refreshid >&nbsp;<button class="btn_save" onclick="changeValue(document.getElementById('refreshid').value, 'set_int?refresh=', 'config')">Save</button></td></tr>
		<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
		<tr><td class="pc1">Image quality</td><td class="pc2">Low <input type="range" class="slider" name="photo_quality" id=photo_qualityid min="10" max="63" step="1" onchange="changeValue(this.value, 'set_int?photo_quality=', 'config')"> High</td></tr>
		<tr>
			<td class="pc1">Resolution</td><td><label for="framesize"></label>
				<select class="select" id="framesizeid" name="framesize" onchange="changeValue(this.value, 'set_int?framesize=', 'config')">
					<option value="0">320x240</option>
					<option value="1">352x288</option>
					<option value="2">640x480</option>
					<option value="3">800x600</option>
					<option value="4">1024x768</option>
					<option value="5">1280x1024</option>
					<option value="6">1600x1200</option>
				</select> <span class="pc1">pixels</span>
			</td>
		</tr>
		<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
		<tr><td class="pc1">Brightness</td><td class="pc2">Low <input type="range" class="slider" name="brightness" id=brightnessid min="-2" max="2" step="1" onchange="changeValue(this.value, 'set_int?brightness=', 'config')">High</td></tr>
		<tr><td class="pc1">Contrast</td><td class="pc2">Low <input type="range" class="slider" name="contrast" id=contrastid min="-2" max="2" step="1" onchange="changeValue(this.value, 'set_int?contrast=', 'config')"> High</td></tr>
		<tr><td class="pc1">Saturation</td><td class="pc2">Low <input type="range" class="slider" name="saturation" id=saturationid min="-2" max="2" step="1" onchange="changeValue(this.value, 'set_int?saturation=', 'config')"> High</td></tr>
		<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
		<tr>
			<td class="pc1">Image Rotation</td><td><label for="image_rotation"></label>
				<select class="select" id="image_rotationid" name="image_rotation" onchange="changeValue(this.value, 'set_int?image_rotation=', 'config')">
					<option value="1">0°</option>
					<option value="6">90°</option>
					<option value="3">180°</option>
					<option value="8">270°</option>
				</select>
			</td>
		</tr>
		<tr><td class="pc1">Horizontal mirror</td><td class="pc2"><label class="switch"><input type="checkbox" name="hmirror" id=hmirrorid  onchange="changeValue(this.checked, 'set_bool?hmirror=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_hmirror"></span></td></tr>
		<tr><td class="pc1">Vertical flip</td><td class="pc2"><label class="switch"><input type="checkbox" name="vflip" id=vflipid onchange="changeValue(this.checked, 'set_bool?vflip=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_vflip"></span></td></tr>
		<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
		<tr><td class="pc1">LED light</td><td class="pc2"><label class="switch"><input type="checkbox" name="led" id=ledid onchange="changeValue(this.checked, 'action_led?/led=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_led"></span></td></tr>
		<tr><td class="pc1">LED flash</td><td class="pc2"><label class="switch"><input type="checkbox" name="flash" id=flashid onchange="changeValue(this.checked, 'set_bool?flash=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_flash"></span></td></tr>
		<tr><td class="pc1">Flash duration</td><td class="pc2">Low <input type="range" class="slider" name="flash_time" id=flash_timeid min="50" max="1500" step="50" onchange="changeValue(this.value, 'set_int?flash_time=', 'config')">High</td></tr>
		<tr><td class="pc1">Flash duration</td><td class="pc2"><span id="flash_time_value"></span> ms</td></tr>
		<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
		<tr><td class="pc1">Save images to micro SD</td><td class="pc2"><label class="switch"><input type="checkbox" name="timelaps" id=timelapsid onchange="changeValue(this.checked, 'set_bool?timelaps_enable=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_timelaps"></span></td></tr>
		<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
	</table></center>
	<center><button class="btn_collapsible">Advanced settings</button></center>
	<div class="content">
		<center><table id="data">
			<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
			<tr><td class="ps3">Advanced settings</td><td></td></tr>
			<tr><td class="pc1">Automatic white balancing</td><td class="pc2"><label class="switch"><input type="checkbox" name="awb" id=awbid  onchange="changeValue(this.checked, 'set_bool?awb=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_awb"></span></td></tr>
			<tr><td class="pc1">Automatic white balancing gain</td><td class="pc2"><label class="switch"><input type="checkbox" name="awb_gain" id=awb_gainid  onchange="changeValue(this.checked, 'set_bool?awb_gain=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_awb_gain"></span></td></tr>
			<tr>
				<td class="pc1">Automatic white balancing mode</td><td><label for="wb_mode"></label>
					<select class="select" id="wb_modeid" name="wb_mode" onchange="changeValue(this.value, 'set_int?wb_mode=', 'config')">
						<option value="0">Auto</option>
						<option value="1">Sunny</option>
						<option value="2">Office</option>
						<option value="3">Home</option>
					</select>
				</td>
			</tr>
			<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
			<tr><td class="pc1">Automatic Exposure Control</td><td class="pc2"><label class="switch"><input type="checkbox" name="exposure_ctrl" id=exposure_ctrlid onchange="changeValue(this.checked, 'set_bool?exposure_ctrl=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_exposure_ctrl"></span></td></tr>
			<tr><td class="pc1">Second Level Automatic Exposure Control</td><td class="pc2"><label class="switch"><input type="checkbox" name="aec2" id=aec2id onchange="changeValue(this.checked, 'set_bool?aec2=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_aec2"></span></td></tr>
			<tr><td class="pc1">Automatic exposure level</td><td class="pc2">Low <input type="range" class="slider" name="ae_level" id=ae_levelid min="-2" max="2" step="1" onchange="changeValue(this.value, 'set_int?ae_level=', 'config')"> High</td></tr>
			<tr><td class="pc1">Automatic exposure time</td><td class="pc2">Low <input type="range" class="slider" name="aec_value" id=aec_valueid min="0" max="1200" step="10" onchange="changeValue(this.value, 'set_int?aec_value=', 'config')">High</td></tr>
			<tr><td class="pc1">Automatic exposure time</td><td class="pc2"><span id="aec_value_value"></span> ms</td></tr>
			<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
			<tr><td class="pc1">Automatic gain control</td><td class="pc2"><label class="switch"><input type="checkbox" name="gain_ctrl" id=gain_ctrlid onchange="changeValue(this.checked, 'set_bool?gain_ctrl=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_gain_ctrl"></span></td></tr>
			<tr><td class="pc1">Automatic gain control level</td><td class="pc2">Low <input type="range" class="slider" name="agc_gain" id=agc_gainid min="0" max="30" step="1" onchange="changeValue(this.value, 'set_int?agc_gain=', 'config')">High</td></tr>
			<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
			<tr><td class="pc1">Bad pixel correction</td><td class="pc2"><label class="switch"><input type="checkbox" name="bpc" id=bpcid onchange="changeValue(this.checked, 'set_bool?bpc=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_bpc"></span></td></tr>
			<tr><td class="pc1">White pixel correction</td><td class="pc2"><label class="switch"><input type="checkbox" name="wpc" id=wpcid onchange="changeValue(this.checked, 'set_bool?wpc=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_wpc"></span></td></tr>
			<tr><td class="pc1">Raw gamma correction</td><td class="pc2"><label class="switch"><input type="checkbox" name="raw_gama" id=raw_gamaid onchange="changeValue(this.checked, 'set_bool?raw_gama=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_raw_gama"></span></td></tr>
			<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
			<tr><td class="pc1">Lens correction</td><td class="pc2"><label class="switch"><input type="checkbox" name="lenc" id=lencid onchange="changeValue(this.checked, 'set_bool?lenc=', 'config')"><span class="checkbox_slider round"></span></label> <span id="status_lensc"></span></td></tr>
		</table></center>
	</div>
</body>
<script src="scripts.js"></script>
<script>
	get_data("config");
	setupCollapsibleButtons();
</script>
)rawliteral";

/* ------------------------------------------------------------------------------------------------------------ */
const char page_system_html[] PROGMEM = R"rawliteral(
<style>@import url("styles.css?v=1.0.0");</style>
<script src="jquery-3.7.0.min.js"></script>
<body>
	<center>
        <table id="data">
            <tr><td class="ps3">Status</td><td></td></tr>
            <tr><td class="ps1">Prusa Connect Status</td><td class="ps2" id="last_upload_status"></td></tr>
            <tr><td class="ps1">Wi-Fi mode</td><td class="ps2" id="wifi_mode"></td></tr>
			<tr><td class="ps1">Wi-Fi service AP SSID</td><td class="ps2" id="service_ap_ssid"></td></tr>
            <tr><td class="ps1">Uptime</td><td class="ps2" id="uptime"></td></tr>
			<tr><td class="ps1">ESP32 Temperature</td><td class="ps2" id="mcu_temp"></td></tr>
			<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
			<tr><td class="ps3">Firmware</td><td></td></tr>
            <tr><td class="ps1">Version</td><td class="ps2" id="sw_ver"></td></tr>
			<tr><td class="ps1">Build</td><td class="ps2" id="sw_build"></td></tr>
            <tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
			<tr><td class="ps3">Configuration</td><td></td></tr>
			<tr><td class="pc1">Camera name & mDNS record</td><td ><input type="text" name="mdns" id=mdnsid ><span class=pc1>.local</span>&nbsp;<button class="btn_save" onclick="changeValue(document.getElementById('mdnsid').value, 'set_mdns?mdns=', 'system')">Save</button></td></tr>
			<tr>
			    <td class="pc1">Log level</td><td><label for="loglevel"></label>
				<select class="select" id="loglevelid" name="loglevel" onchange="changeValue(this.value, 'set_int?log_level=', 'system')">
					<option value="0">Error</option>
					<option value="1">Warning</option>
					<option value="2">Info</option>
					<option value="3">Verbose</option>
				</select>
			   </td>
		   </tr>
		   <tr><td class="pc1">Get logs</td><td ><button class="btn_update" onclick="window.open('get_logs')">Get logs</button></td></tr>
		   <tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
		   <tr><td class="ps3">Micro SD card</td><td></td></tr>
		   <tr><td class="ps1">Card status</td><td class="ps2" id="sd_status"></td></tr>
		   <tr><td class="ps1">Capacity</td><td class="ps2"><span id="sd_total"></span> MB</td></tr>
		   <tr><td class="ps1">Available</td><td class="ps2"><div class="progress-container"><div class="progress-bar" id="progress_bar_sd_free">0%</div></div></td></tr>
		   <tr><td class="ps1">Used</td><td class="ps2"><div class="progress-container"><div class="progress-bar" id="progress_bar_sd_used">0%</div></div></td></tr>
        </table>
    </center>
    <br>
    <center>
        <table id="update">
            <tr><td class="ps3">Firmware update</td><td></td></tr>
			<tr><td class="ps1">Available from cloud</td><td class="ps2"><span id="sw_new_ver"></span> &nbsp;<button class="btn_update" onclick="checkUpdate()">Check for Updates</button></td></tr>
            <tr><td class="ps1">Status</td><td><span class="ps2" id="status">Ready</span></td></tr>
			<tr><td class="ps1">Progress</td><td class="ps2"><div class="progress-container"><div class="progress-bar" id="myProgressBar">0%</div></div></td></tr>
            <tr><td></td><td><input type="file" id="firmwareInput" accept=".bin"></td></tr>
            <tr><td></td><td><input type="submit" class="btn_update" value="Update from File" onclick="uploadFile()"></td></tr>
			<tr><td></td><td><input type="submit" class="btn_update" value="Update from Cloud" onclick="updateWeb()"></td></tr>
        </table>
    </center>
</body>
<script src="scripts.js"></script>
<script>
    var updateCompleted = false;
	var updateInterval = setInterval(updateProgress, 800);
	get_data("system");
</script>
)rawliteral";

/* ------------------------------------------------------------------------------------------------------------ */
const char page_temperature_html[] PROGMEM = R"rawliteral(
<style>@import url("styles.css?v=1.0.0");</style>
<script src="jquery-3.7.0.min.js"></script>
<body>
	<center>
		<table>
			<tr><td class=pa3>External temperature sensor DHT22/DHT11</td><td></td></tr>
			<tr><td class=pa1 align="right">Enable sensors</td><td><label class="switch"><input type="checkbox" name="extsens_en" id="extsetsid" onchange="changeValue(this.checked, 'set_bool?extsens_enable=', 'temp')"><span class="checkbox_slider round"></span></label></label> <span class=pa1 id="status_extsens"></span></td></tr>
            <tr><td class="ps1">Sensor status: </td><td class="pa2" id="extsens_stat"></td></tr>
			<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
            <tr>
			    <td class="pa1">Temperature Unit</td><td><label for="temp_unit"></label>
				<select class="select" id="temp_unitid" name="temp_unit" onchange="changeValue(this.value, 'set_int?temp_unit=', 'temp')">
					<option value="0">Celsius</option>
					<option value="1">Fahrenheit</option>
				</select>
			   </td>
		    </tr>
			<tr><td style="height: 1px;"></td><td style="height: 1px;"></td></tr>
			<tr><td class="pa1">Temperature</td><td class="pa2" id="ext_temp"></td></tr>
            <tr><td class="pa1">Humidity</td><td class="pa2" id="ext_hum"></td></tr>
		</table>
	</center>
</body>
<script src="scripts.js"></script>
<script>
	get_data("temp");
</script>
)rawliteral";

/* ------------------------------------------------------------------------------------------------------------ */
const char styles_css[] PROGMEM = R"rawliteral(
body {
    font-family: sans-serif;
}
/* index styles */
.p1 {
    color: #797979;
    font: normal normal normal 18px/5px sans-serif;
    letter-spacing: 0px;
}
.p2 {
    text-align: left;
    font: normal normal bold 14px/20px sans-serif;
    letter-spacing: 0px;
    color: #808080;
    opacity: 1;
    display: inline-block;
}
.p3 {
    text-align: left;
    font: normal normal normal 14px/20px sans-serif;
    letter-spacing: 0px;
    color: #808080;
    opacity: 1;
    display: inline-block;
}
.p4 {
    text-align: left;
    font: normal normal normal 14px/20px sans-serif;
    letter-spacing: 0px;
    color: #808080;
    opacity: 1;
}
.p5 {
    text-align: center;
    font: normal normal bold 14px/20px sans-serif;
    letter-spacing: 0px;
    color: #000000;
    opacity: 1;
}
/* NAVIGATION BAR */
nav {
    display: flex;
    background-color: transparent;
}
.top_bar {
    display: flex;
    width: 100%;
}
.top_bar li {
    display: inline-block;
    padding: 5px;
}
.top_bar li a {
    text-decoration: none;
    cursor: pointer;
    display: flex;
    align-items: center;
}
.top_bar li a:hover {
    text-decoration: underline #fa6831;
    text-underline-position: under;
    text-underline-offset: 8px;
    text-decoration-thickness: 2px;
}
#links li a.active {
    text-decoration: underline #fa6831;
    text-underline-position: under;
    text-underline-offset: 8px;
    text-decoration-thickness: 2px;
}
/* CFG BAR */
#cfg {
    display: flex;
    flex-direction: column;
    text-align: center;
    font: normal normal bold 14px/20px sans-serif;
    letter-spacing: 0px;
    color: #2A2A2A;
    opacity: 1;
}
#cfg_bar li {
    display: inline-block;
    padding: 14px;
    font-size: 16px;
    left: 50%;
}
#cfg_bar li a {
    text-decoration: none;
    cursor: pointer;
    color: #212529;
}
#cfg_bar li a:hover {
    color: #fa6831;
}
/* CONTAINER */
 .container {
     display: table;
     height: 100%;
     width: 100%;
}
.container_left-half {
    grid-column: 1;
    display: table-cell;
    vertical-align: middle;
    width: 50%;
    text-align: center;
}
.container_right-half {
    grid-column: 2;
    display: table-cell;
    vertical-align: middle;
    width: 50%;
}
/* CHECKBOX SLIDER */
.switch {
    position: relative;
    display: inline-block;
    width: 30px;
    height: 17px;
    vertical-align: middle;
}
.switch input {
    opacity: 0;
    width: 0;
    height: 0;
}
.checkbox_slider {
    position: absolute;
    cursor: pointer;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background-color: #ccc;
    -webkit-transition: .4s;
    transition: .4s;
}
.checkbox_slider:before {
    position: absolute;
    content: "";
    height: 13px;
    width: 13px;
    left: 2px;
    bottom: 2px;
    background-color: white;
    -webkit-transition: .4s;
    transition: .4s;
}
input:checked+.checkbox_slider {
    background-color: #797979;
}
input:focus+.checkbox_slider {
    box-shadow: 0 0 1px #797979;
}
input:checked+.checkbox_slider:before {
    -webkit-transform: translateX(13px);
    -ms-transform: translateX(13px);
    transform: translateX(13px);
}
.checkbox_slider.round {
    border-radius: 13px;
}
.checkbox_slider.round:before {
    border-radius: 50%;
}
/* BUTTON */
.btn {
    width: 306px;
    height: 30px;
    text-align: center;
    font: normal normal bold 14px/5px sans-serif;
    color: #000000;
    background-color: white;
    border-radius: 5px;
    border: 1px solid #343a40;
}
.btn:hover {
    background-color: #FA6831;
    color: white;
}
/* BOTTON table */
#botton {
    width: 100%;
    text-align: center;
    background: #F5F5F5 0% 0% no-repeat padding-box;
    opacity: 1;
    bottom: 0;
}
/* ----- styles config ----- */
.pc1 {
    text-align: right;
    font: normal normal normal 11px/5px sans-serif;
    letter-spacing: 0px;
    color: #797979;
    opacity: 1;
}
.pc2 {
    text-align: left;
    font: normal normal normal 12px/5px sans-serif;
    letter-spacing: 0px;
    color: #000000;
    opacity: 1;
}
.pc3 {
    text-align: right;
    font: normal normal normal bold 12px/17px sans-serif;
    letter-spacing: 0px;
    color: #2A2A2A;
    opacity: 1;
}
/* data table */
#data {
    font-family: Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
    table-layout: fixed;
}
#data td, #data th {
    padding: 8px;
}
#data th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
}
/* BUTTON */
.btn_save {
    width: 69px;
    height: 24px;
    text-align: center;
    font: normal normal bold 14px/5px sans-serif;
    color: #000000;
    background-color: white;
    border-radius: 5px;
    border: 1px solid #343a40;
}
.btn_save:hover {
    background-color: #FA6831;
    color: white;
}
/* RANGE */
.slider {
    -webkit-appearance: none;
    width: 133px;
    height: 10px;
    border-radius: 5px;
    background: linear-gradient(to right, #d3d3d3 50%, #FA6831 50%);
    outline: none;
}
.slider::-webkit-slider-thumb {
    -webkit-appearance: none;
    appearance: none;
    width: 16px;
    height: 16px;
    border-radius: 50%;
    background: #FA6831;
    cursor: pointer;
}
.slider::-moz-range-thumb {
    width: 16px;
    height: 16px;
    border-radius: 50%;
    background: #FA6831;
    cursor: pointer;
}
/* ----- styles wifi ----- */
.w1 {
    text-align: left;
    font: normal normal bold 12px/17px sans-serif;
    letter-spacing: 0px;
    color: #2A2A2A;
    opacity: 1;
}
.w2 {
    font: normal normal normal 11px/5px sans-serif;
    letter-spacing: 0px;
    color: #797979;
    opacity: 1;
}
.w2 span {
    vertical-align: middle;
}
#center_tb {
    border-collapse: collapse;
    width: 100%;
    table-layout: fixed;
    text-align: left;
}
#wificfg_tb {
    margin-left: 30%;
}
/* wifi_ntw table */
#wifi_ntw {
    font: normal normal normal 12px/5px sans-serif;
    border-collapse: collapse;
    width: 100%;
    table-layout: fixed;
    text-align: left;
}
#wifi_ntw td {
    border-bottom: 1px solid #ddd;
    padding: 8px;
}
#wifi_ntw tr:nth-child(even) {
    background: #F8F8F8 0% 0% no-repeat padding-box;
}
#wifi_ntw tr:hover {
    background-color: #ddd;
}
#wifi_ntw th {
    background-color: transparent;
    text-align: left;
    font: normal normal bold 13px/11px sans-serif;
    letter-spacing: 0px;
    color: #2A2A2A;
    opacity: 1;
}
#wifi_ntw tr {
    border-bottom: 1px solid #ccc;
}
#wifi_ntw img {
    width: 19px;
    height: 12px;
}
/* BUTTON */
.btn_save_w {
    width: 178px;
    height: 24px;
    text-align: center;
    font: normal normal bold 14px/5px sans-serif;
    color: #000000;
    background-color: white;
    border-radius: 5px;
    border: 1px solid #343a40;
}
.btn_save_w:hover {
    background-color: #FA6831;
    color: white;
}
/* ----- styles auth ----- */
.pa1 {
    text-align: right;
    font: normal normal normal 11px/5px sans-serif;
    letter-spacing: 0px;
    color: #797979;
    opacity: 1;
}
.pa2 {
    text-align: left;
    font: normal normal bold 12px/17px sans-serif;
    letter-spacing: 0px;
    color: #2A2A2A;
    opacity: 1;
}
.pa3 {
    text-align: right;
    font: normal normal normal bold 12px/17px sans-serif;
    letter-spacing: 0px;
    color: #2A2A2A;
    opacity: 1;
}
/* BUTTON */
.btn_save_a {
    width: 178px;
    height: 24px;
    text-align: center;
    font: normal normal bold 14px/5px sans-serif;
    color: #000000;
    background-color: white;
    border-radius: 5px;
    border: 1px solid #343a40;
}
.btn_save_a:hover {
    background-color: #FA6831;
    color: white;
}
.toggle-password {
    position: relative;
    cursor: pointer;
}
.toggle-password img {
    position: absolute;
    top: 50%;
    right: 0;
    transform: translateY(-50%);
}
.password-container {
    display: flex;
    align-items: center;
}
#auth_password.reveal {
    -webkit-text-security: none;
}
#auth_password {
    -webkit-text-security: disc;
}
/* ----- styles system ----- */
.ps1 {
    text-align: right;
    font: normal normal normal 11px/5px sans-serif;
    letter-spacing: 0px;
    color: #797979;
    opacity: 1;
}
.ps2 {
    text-align: left;
    font: normal normal normal 12px/5px sans-serif;
    letter-spacing: 0px;
    color: #000000;
    opacity: 1;
}
.ps3 {
    text-align: right;
    font: normal normal normal bold 12px/17px sans-serif;
    letter-spacing: 0px;
    color: #2A2A2A;
    opacity: 1;
}
/* update table */
#update {
     font-family: Arial, Helvetica, sans-serif;
     border-collapse: collapse;
     width: 100%;
     table-layout: fixed;
}
#update td, #update th {
     padding: 8px;
}
#update th {
     padding-top: 12px;
     padding-bottom: 12px;
     text-align: left;
}
/* BUTTON */
.btn_update {
     width: 178px;
     height: 24px;
     text-align: center;
     font: normal normal bold 14px/5px sans-serif;
     color: #000000;
     background-color: white;
     border-radius: 5px;
     border: 1px solid #343a40;
}
.btn_update:hover {
     background-color: #FA6831;
     color: white;
}
.underlined-text {
     text-decoration: underline;
     color: blue;
     cursor: pointer;
}
/* progress bar*/
.progress-container {
     width: 30%;
     background-color: #ccc;
}
.progress-bar {
     width: 0px;
     height: 15px;
     background-color: #FA6831;
     text-align: center;
     line-height: 15px;
     color: white;
     padding-left: 3px;
}
/* advanced cam cfg */
.content {
    display: none;
}
.btn_collapsible {
    width: 300px;
    height: 24px;
    text-align: center;
    font: normal normal bold 14px/5px sans-serif;
    color: #000000;
    background-color: white;
    border-radius: 5px;
    border: 1px solid #343a40;
}
.btn_collapsible:hover {
    background-color: #FA6831;
    color: white;
}
/* advanced wifi cfg */
.content_wifi {
    display: none;
}
.btn_collapsible_wifi {
    width: 300px;
    height: 24px;
    text-align: center;
    font: normal normal bold 14px/5px sans-serif;
    color: #000000;
    background-color: white;
    border-radius: 5px;
    border: 1px solid #343a40;
}
.btn_collapsible_wifi:hover {
    background-color: #FA6831;
    color: white;
}
)rawliteral";

/* ------------------------------------------------------------------------------------------------------------ */
const char scripts_js[] PROGMEM = R"rawliteral(
function get_data(val) {
	jQuery.ajax({
		url: 'json_input',
		type: 'GET',
		timeout: 5000,
		success: function(data) {
			console.log("Incommming data: ");
			console.log(data);
			var obj = JSON.parse(data);
			console.log(obj);

			if (!document.querySelector('#light-icon img')) {
				var img = document.createElement('img');
				img.src = (obj.led == "true") ? 'light-on-icon.svg' : 'light-off-icon.svg';
				document.getElementById('light-icon').appendChild(img);
			}
			document.title = obj.mdns;
			
			if (val == "config") {
				$("#fingerprint").text(obj.fingerprint);
				$("#refreshInterval").text(obj.refreshInterval);
				document.getElementById('tokenid').value = obj.token;
				document.getElementById('refreshid').value = obj.refreshInterval;
				document.getElementById('photo_qualityid').value = obj.photoquality;
				document.getElementById('framesizeid').value = obj.framesize;
				document.getElementById('brightnessid').value = obj.brightness;
				document.getElementById('contrastid').value = obj.contrast;
				document.getElementById('saturationid').value = obj.saturation;
				document.getElementById('image_rotationid').value = obj.image_rotation;
				document.getElementById('hmirrorid').checked = obj.hmirror;
				document.getElementById('vflipid').checked = obj.vflip;
				document.getElementById('lencid').checked = obj.lensc;
				document.getElementById('exposure_ctrlid').checked = obj.exposure_ctrl;
				document.getElementById('awbid').checked = obj.awb;
				document.getElementById('awb_gainid').checked = obj.awb_gain;
				document.getElementById('wb_modeid').value = obj.wb_mode;
				document.getElementById('ledid').checked = obj.led;
				document.getElementById('flashid').checked = obj.flash;
				document.getElementById('flash_timeid').value = obj.flash_time;
				document.getElementById('bpcid').checked = obj.bpc;
				document.getElementById('wpcid').checked = obj.wpc;
				document.getElementById('raw_gamaid').checked = obj.raw_gama;
				document.getElementById('aec2id').checked = obj.aec2;
				document.getElementById('ae_levelid').value = obj.ae_level;
				document.getElementById('aec_valueid').value = obj.aec_value;
				document.getElementById('gain_ctrlid').checked = obj.gain_ctrl;
				document.getElementById('agc_gainid').value = obj.agc_gain;
				document.getElementById("flash_time_value").innerText = obj.flash_time;
				document.getElementById("aec_value_value").innerText = obj.aec_value;
				document.getElementById('timelapsid').checked = obj.timelaps;
				$("#status_hmirror").text((obj.hmirror == "true") ? "On" : "Off");
				$("#status_vflip").text((obj.vflip == "true") ? "On" : "Off");
				$("#status_lensc").text((obj.lensc == "true") ? "On" : "Off");
				$("#status_exposure_ctrl").text((obj.exposure_ctrl == "true") ? "On" : "Off");
				$("#status_awb").text((obj.awb == "true") ? "On" : "Off");
				$("#status_awb_gain").text((obj.awb_gain == "true") ? "On" : "Off");
				$("#status_led").text((obj.led == "true") ? "On" : "Off");
				$("#status_flash").text((obj.flash == "true") ? "On" : "Off");
				$("#status_bpc").text((obj.bpc == "true") ? "On" : "Off");
				$("#status_wpc").text((obj.wpc == "true") ? "On" : "Off");
				$("#status_raw_gama").text((obj.raw_gama == "true") ? "On" : "Off");
				$("#status_aec2").text((obj.aec2 == "true") ? "On" : "Off");
				$("#status_gain_ctrl").text((obj.gain_ctrl == "true") ? "On" : "Off");
				$("#status_timelaps").text((obj.timelaps == "true") ? "On" : "Off");
				sliderCheck();
			}

			if (val == "auth") {
				document.getElementById('authid').checked = obj.auth;
				$("#status_auth").text((obj.auth == "true") ? "On" : "Off");
				document.getElementById('auth_username').value = obj.auth_username;
			}

			if (val == "wifi") {
				document.getElementById('serviceapid').checked = obj.serviceap;
				$("#status_serviceap").text((obj.serviceap == "true") ? "On" : "Off");
				$("#ssid").text(obj.ssid);
				$("#rssi").text(obj.rssi);
				$("#rssi_percentage").text(obj.rssi_percentage);
				$("#ip").text(obj.ip);
				$("#mdns").text(obj.mdns);
				$("#wifi_network_status").text(obj.wifi_network_status);
				document.getElementById('ipcfgid').value = obj.ip_cfg;
				document.getElementById('net_ip_id').value = obj.net_ip;
				document.getElementById('net_mask_id').value = obj.net_mask;
				document.getElementById('net_gw_id').value = obj.net_gw;
				document.getElementById('net_dns_id').value = obj.net_dns;

				if (!document.querySelector('#main-wifi-signal wifi_img')) {
					var wifi_img = document.createElement('wifi_img');
					wifi_img.width = 19;
					wifi_img.height = 12;
					wifi_img.src = getIconPath(obj.rssi);
					document.getElementById('main-wifi-signal').appendChild(wifi_img);
				}
			}

			if (val == "system") {
				$("#uptime").text(obj.uptime);
				$("#sw_ver").text(obj.sw_ver);
				$("#sw_build").text(obj.sw_build);
				$("#last_upload_status").text(obj.last_upload_status);
				$("#wifi_mode").text(obj.wifi_mode);
				$("#sw_new_ver").text(obj.sw_new_ver);
				$("#service_ap_ssid").text(obj.service_ap_ssid);
				$("#sd_status").text(obj.sd_status);
				$("#sd_total").text(obj.sd_total);
				$("#sd_free_p").text(obj.sd_free_p);
				$("#sd_used_p").text(obj.sd_used_p);
				$("#mcu_temp").text(obj.mcu_temp);

				var sd_free_prog = document.getElementById("progress_bar_sd_free");
				sd_free_prog.style.width = obj.sd_free_p + "%";
				sd_free_prog.innerHTML = obj.sd_free_p + "%";

				var sd_free_prog = document.getElementById("progress_bar_sd_used");
				sd_free_prog.style.width = obj.sd_used_p + "%";
				sd_free_prog.innerHTML = obj.sd_used_p + "%";

				document.getElementById('mdnsid').value = obj.mdns;
        		document.getElementById('loglevelid').value = obj.log_level;
			}

			if (val == "temp") {
				$("#extsens_stat").text(obj.extsens_stat);
				document.getElementById('extsetsid').checked = obj.extsen_en;
				document.getElementById('temp_unitid').value = obj.exttemp_unit;
				$("#ext_temp").text(obj.ext_temp);
				$("#ext_hum").text(obj.ext_hum);
			}
		},
		error: function(html) {
			console.log("json Timeout or error");
			//alert("jquery timeout or comunication error");
		}
	});
}

function sliderCheck() {
	var ranges = document.querySelectorAll(".slider");
	ranges.forEach(function(range) {
		var percent = (range.value - range.min) / (range.max - range.min) * 100;
		var gradient = "linear-gradient(to right, #FA6831 " + percent + "%, #d3d3d3 " + percent + "%)";
		range.style.background = gradient;
		range.oninput = function() {
			var percent = (this.value - this.min) / (this.max - this.min) * 100;
			var gradient = "linear-gradient(to right, #FA6831 " + percent + "%, #d3d3d3 " + percent + "%)";
			this.style.background = gradient;
		}
	});
}

function getIconPath(rssi) {
	let path;
	if (rssi == 0) {
		path = 'wifi-icon-0.svg';
	} else if (rssi <= -70) {
		path = 'wifi-icon-1.svg';
	} else if (rssi > -70 && rssi <= -60) {
		path = 'wifi-icon-2.svg';
	} else if (rssi > -60 && rssi <= -50) {
		path = 'wifi-icon-3.svg';
	} else {
		path = 'wifi-icon-4.svg';
	}
	return path;
}

var OpenImageclickCount = 0;

function openImage() {
	var img = document.getElementById("photo");
	if (OpenImageclickCount % 2 == 0) {
		img.style.position = "fixed";
		img.style.top = "5%";
		img.style.left = "5%";
		img.style.width = "auto";
		img.style.height = "auto";
		img.style.maxWidth = "100%";
		img.style.maxHeight = "90%";
		img.style.zIndex = "9999";
	} else {
		img.style.position = "";
		img.style.top = "";
		img.style.left = "";
		img.style.width = "";
		img.style.height = "";
		img.style.zIndex = "";
	}
	OpenImageclickCount++;
}

function actionButton(url, reload, msg) {
    var xhr = new XMLHttpRequest();
    
	if (msg != '') {
		alert(msg);
	}

    xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
            if (reload == true) {
                setTimeout(function() {
                    location.reload();
                }, 200);
            }
        }
    };

    xhr.open('GET', url, true);
    xhr.send();
}

function setActive(link) {
	var links = document.querySelectorAll('#links li a');
	links.forEach(function(item) {
		item.classList.remove('active');
	});
	link.classList.add('active');
}

var links = document.querySelectorAll('#links li a');
links.forEach(function(link) {
	link.addEventListener('click', function() {
		setActive(link);
	});
});

function addClickListener(id) {
    var link = document.getElementById(id);
    if (!link.hasOwnProperty('clickListener')) {
        link.addEventListener('click', function(event) {
            event.preventDefault();
            window.open(link.href, '_blank');
        });
        link.clickListener = true;
    }
}

/* wifi page */
function setWifi(val_ssid, val_pass) {
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open("GET", "wifi_cfg?wifi_ssid=" +  encodeURIComponent(val_ssid) + "&wifi_pass=" + encodeURIComponent(val_pass), false);
	xmlHttp.send(null);
	alert(xmlHttp.responseText);
	get_data("wifi");
}

function setWifiNet(val_ip, val_mask, val_gw, val_dns) {	
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open("GET", "wifi_net_cfg?ip=" +  encodeURIComponent(val_ip) + "&mask=" + encodeURIComponent(val_mask) + "&gw=" + encodeURIComponent(val_gw) + "&dns=" + encodeURIComponent(val_dns), false);
	xmlHttp.send(null);
	alert(xmlHttp.responseText);
	get_data("wifi");
}

function scanWifi() {
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open("GET", "wifi_scan?", false);
	xmlHttp.send(null);
	alert(xmlHttp.responseText);
	get_data("wifi");
	setTimeout(function() {
		GetDataAndPrintTableWiFi();
	}, 8000);
}

function GetDataAndPrintTableWiFi() {
	$("#wifi_ntw").find("tr:gt(0)").remove();
	$.ajax({
		url: 'json_wifi',
		type: 'GET',
		timeout: 15000,
		dataType: 'json',
		data: {},

		success: function(data) {
			for (var i = 0; i < data.length; i++) {
				const IconName = "wifi-icon-" + i;
				var row = $('<tr><td>' + data[i].ssid + '</td><td><div id="' + IconName + '" style="display: flex; align-items: center;"></div></td><td>' + data[i].channel + '</td><td>' + data[i].encryption + '</td></tr>');
				$('#wifi_ntw').append(row);

				if (!document.querySelector('#' + IconName + ' img')) {
					var img = document.createElement('img');
					img.src = getIconPath(data[i].rssi);
					document.getElementById(IconName).prepend(img);
					document.getElementById(IconName).append(data[i].rssi_percentage);
					document.getElementById(IconName).append("% / ");
					document.getElementById(IconName).append(data[i].rssi);
					document.getElementById(IconName).append("dBm");
				}
			}
		},
		error: function(jqXHR, textStatus, errorThrown) {
			console.log('Error:' + textStatus + '-' + errorThrown);
		}
	});
}

/* auth page */
function setAuth(val_name, val_pass) {
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open("GET", "basicauth_cfg?" + "auth_username=" + encodeURIComponent(val_name) + "&auth_password=" + encodeURIComponent(val_pass), false);
	xmlHttp.send(null);
	alert(xmlHttp.responseText);
	get_data("auth");
}

function changeValue(val, url, reload, msg) {
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open("GET", url + val, false);
	xmlHttp.send(null);
	if ((url == "set_int?refresh=") || (url == "set_token?token=") || (url == "set_mdns?mdns=") || (url == "set_int?ipcfg=")) {
		alert(xmlHttp.responseText);
	}
	if (url == "set_flash_time?flash_time=") {
		document.getElementById("flash_time_value").innerText = val;
	}
	get_data(reload);
}

function togglePasswordVisibility() {
	const passwordInput = document.getElementById("auth_password");
	const eyeIcon = document.getElementById("eye-icon");
	if (passwordInput.getAttribute("type") === "password") {
		passwordInput.setAttribute("type", "text");
		passwordInput.classList.add("reveal");
		eyeIcon.src = "eye-slash.svg";
		eyeIcon.alt = "Hide Password";
	} else {
		passwordInput.setAttribute("type", "password");
		passwordInput.classList.remove("reveal");
		eyeIcon.src = "eye.svg";
		eyeIcon.alt = "Show Password";
	}
}

/* system page */
if (typeof uploadingFirmware === 'undefined') {
	var uploadingFirmware = false;
}

if (typeof FileSize === 'undefined') {
	var FileSize = 0;
}

function uploadFile() {
	alert("Started updating...");
	const firmwareInput = document.getElementById('firmwareInput');
	const statusDiv = document.getElementById('status');
	const file = firmwareInput.files[0];
	FileSize = file.size;
	SetFirmwareSize(file.size);

	if (file) {
		statusDiv.innerText = 'Updating...';
		const formData = new FormData();
		formData.append('firmware', file);
		uploadingFirmware = true;

		fetch('/upload', {
				method: 'POST',
				body: formData,
			})
			.then((response) => {
				if (response.ok) {
					response.text().then((data) => {
						const jsonData = JSON.parse(data);
						updateProgress();
						uploadingFirmware = false;
						if (jsonData.errorMessage) {
							alert(`Error message: ${jsonData.errorMessage}`);
						}
					});
				} else {
					uploadingFirmware = false;
					response.text().then((errorMessage) => {
						alert(`Error message: ${errorMessage}`);
					});
				}
			})
			.catch((error) => {
				console.error('Error:', error);
				uploadingFirmware = false;
			});
	} else {
		statusDiv.innerText = 'No file selected';
	}
}

function SetFirmwareSize(val) {
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open("GET", "set_firmware_size?size=" + val, false);
	xmlHttp.send(null);
}

function updateProgress() {
	if (!uploadingFirmware) {
		return;
	}

	fetch('/UpdateProcessing', {
			method: 'GET',
		})
		.then((response) => {
			if (response.ok) {
				return response.json();
			} else {
				throw new Error('Failed to fetch progress');
			}
		})
		.then((data) => {
			const statusDiv = document.getElementById('status');
			var progressBar = document.getElementById("myProgressBar");
			progressBar.style.width = data.processed_percent + "%";
			progressBar.innerHTML = data.processed_percent + "%";

			statusDiv.innerText = data.message;
			uploadingFirmware = data.updating;
			if (data.updating == false  && !updateCompleted) {
				alert('Operation done. Please reboot MCU.');
				uploadingFirmware = false;
				updateCompleted = true;
				clearInterval(updateInterval);
			}
		})
		.catch((error) => {
			console.error('Error:', error);
			var progressBar = document.getElementById("myProgressBar");
			progressBar.innerHTML = "Error";
			clearInterval(updateInterval);
		});
}

function checkUpdate() {
	var xmlHttp = new XMLHttpRequest();
	alert("Connecting to server... Please wait several seconds");
	xmlHttp.open("GET", "/check_web_ota_update", false);
	xmlHttp.send(null);
	alert(xmlHttp.responseText);
	get_data("system");
}

function updateWeb() {
	alert("Started updating from cloud.");
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.open("GET", "web_ota_update?update=true", false);
	xmlHttp.send(null);
	uploadingFirmware = true;
}

function validatePasswords() {
    var password = document.getElementById("auth_password").value;
    var confirmPassword = document.getElementById("auth_password_confirm").value;
    var saveButton = document.querySelector(".btn_save_a");
    var passwordStatus = document.getElementById("pass_match");

    if (password === confirmPassword) {
        passwordStatus.innerHTML = "✔️";
        saveButton.disabled = false;
    } else {
        passwordStatus.innerHTML = "❌";
        saveButton.disabled = true;
    }
}

if (document.getElementById("auth_password")) {
	document.getElementById("auth_password").addEventListener("input", validatePasswords);
}

if (document.getElementById("auth_password_confirm")) {
	document.getElementById("auth_password_confirm").addEventListener("input", validatePasswords);
}

if ((document.getElementById("auth_password")) && (document.getElementById("auth_password_confirm"))) {
	validatePasswords();
}

function setupCollapsibleButtons() {
    $(".btn_collapsible").click(function(){
        $(this).toggleClass("active");
        var content = $(this).parent().next();
        if (content.css("display") === "block") {
            content.css("display", "none");
        } else {
            content.css("display", "block");
        }
    });
}

function setupCollapsibleButtonsWiFi() {
    $(".btn_collapsible_wifi").click(function(){
        $(this).toggleClass("active");
        var content_wifi = $(this).parent().next();
        if (content_wifi.css("display") === "block") {
            content_wifi.css("display", "none");
        } else {
            content_wifi.css("display", "block");
        }
    });
}
)rawliteral";

/* ------------------------------------------------------------------------------------------------------------ */
const char license_html[] PROGMEM = R"rawliteral(
<style>@import url("styles.css?v=1.0.0");</style>
<script src="jquery-3.7.0.min.js"></script>
<center><p>The software for device falls under the <a href="https://www.gnu.org/licenses/gpl-3.0.html" id="license-link">GPL-3.0 license terms</a>. To read the license terms please visit <a href="https://www.gnu.org/licenses/gpl-3.0.html" id="license-link-sec">this page</a>.</p></center>
<script src="scripts.js"></script>
<script>
    addClickListener('license-link');
    addClickListener('license-link-sec');
</script>
)rawliteral";

/* ------------------------------------------------------------------------------------------------------------ */
const char gtac_html[] PROGMEM = R"rawliteral(
<style>@import url("styles.css?v=1.0.0");</style>
<script src="jquery-3.7.0.min.js"></script>
<center><p>To read the General Terms and Conditions, please visit <a href="https://www.prusa3d.com/page/general-terms-and-conditions_231236/" id="gtac-link">this page</a>.</p></center>
<script src="scripts.js"></script>
<script>
    addClickListener('gtac-link');
</script>
)rawliteral";

/* ------------------------------------------------------------------------------------------------------------ */
const char privacypolicy_html[] PROGMEM = R"rawliteral(
<style>@import url("styles.css?v=1.0.0");</style>
<script src="jquery-3.7.0.min.js"></script>
<center><p>To read the Privacy Policy, please visit <a href="https://www.prusa3d.com/en/page/privacy-policy_231258/" id="privacy-link">this page</a>.</p></center>
<script src="scripts.js"></script>
<script>
    addClickListener('privacy-link');
</script>
)rawliteral";

/* ------------------------------------------------------------------------------------------------------------ */
const char cookies_html[] PROGMEM = R"rawliteral(
<style>@import url("styles.css?v=1.0.0");</style>
<script src="jquery-3.7.0.min.js"></script>
<center><p>To read the Cookie policy, please visit <a href="https://www.prusa3d.com/en/page/privacy-policy_231258/" id="cookies-link">this page</a>.</p></center>
<script src="scripts.js"></script>
<script>
    addClickListener('cookies-link');
</script>
)rawliteral";

/* EOF  */
