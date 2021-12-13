// index.js
var util = require("../../utils/util.js");

// 获取应用实例
const app = getApp()

var IPAddress1 = "192.168.0.102";
var IPAddress2 = "192.168.4.1";

/**UDP传输图片 */
var udp_jpeg;
var udp_jpeg_port = 8888;

/**UDP传输按键控制命令 */
var udp_cmd;
var udp_cmd_port = 9999;
const arry_buffer = new ArrayBuffer(3);
var uint8_array = new Uint8Array(arry_buffer);


var TimeNumber;//定时器

Page({
  data: {
    imageUrl:"../../images/test_jpg.jpg",
  },
  onLoad() {
    /**UDP传输按键控制命令 */
    udp_cmd = wx.createUDPSocket()//启用UDP
    udp_cmd.bind()

    /**UDP传输图片 */
    udp_jpeg = wx.createUDPSocket()//启用UDP
    udp_jpeg.bind()
    /*定时器 */
    try { clearInterval(TimeNumber); } catch (e) { }
    TimeNumber = setInterval(this.TimeNumberCallBack, 10, "null");
  },
    /**
   * 定时器回调函数
   */
  TimeNumberCallBack: function (arg) {
    /**发送命令获取图像数据 */
    var udp_data =util.StringToHex("55 AA 01 02");
    udp_jpeg.send //ESP32连接路由器的地址
    ({
      address: IPAddress1,
      port: udp_jpeg_port,
      message: udp_data
    });

    udp_jpeg.send //ESP32本身的地址
    ({
      address: IPAddress2,
      port: udp_jpeg_port,
      message: udp_data
    });


    /*发送按键状态 */
    uint8_array[0]=0x55;
    uint8_array[1]=0xAA;
    udp_cmd.send //ESP32连接路由器的地址
    ({
      address: IPAddress1,
      port: udp_cmd_port,
      message: uint8_array,
    });

    udp_cmd.send //ESP32本身的地址
    ({
      address: IPAddress2,
      port: udp_cmd_port,
      message: uint8_array,
    });
  },
  onShow(){

    var that = this
    
    //UDP接收到消息(图片通道)
    udp_jpeg.onMessage(function (res) {
      //console.log('size===' + res.remoteInfo.size)
      var x = new Uint8Array(res.message);
      //if(x[res.remoteInfo.size-1]==0xD9)
      {
        that.setData ({ //把图片数据转给页面显示
          imageUrl: "data:image/png;base64,"+wx.arrayBufferToBase64(x),
        })
      }
    });
  },
  onUnload(){
    udp_jpeg.close();
    udp_cmd.close();
    try { clearInterval(TimeNumber); } catch (e) { }
  },
  bindtouchstart1: function(e){//前进按键按下
    uint8_array[2]=0x01;
  },
  bindtap1: function(e){//前进按键松开
    uint8_array[2] = 0x00;
  },
  bindtouchstart2: function(e){//后退按键按下
    uint8_array[2]=0x02;
  },
  bindtap2: function(e){//后退按键松开
    uint8_array[2] = 0x00;
  },
  bindtouchstart3: function(e){//左转按键按下
    uint8_array[2]=0x03;
  },
  bindtap3: function(e){//左转按键松开
    uint8_array[2] = 0x00;
  },
  bindtouchstart4: function(e){//右转按键按下
    uint8_array[2]=0x04;
  },
  bindtap4: function(e){//右转按键松开
    uint8_array[2] = 0x00;
  }
})
