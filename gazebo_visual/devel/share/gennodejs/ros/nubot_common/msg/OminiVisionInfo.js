// Auto-generated. Do not edit!

// (in-package nubot_common.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let BallInfo = require('./BallInfo.js');
let ObstaclesInfo = require('./ObstaclesInfo.js');
let RobotInfo = require('./RobotInfo.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class OminiVisionInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.ballinfo = null;
      this.obstacleinfo = null;
      this.robotinfo = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('ballinfo')) {
        this.ballinfo = initObj.ballinfo
      }
      else {
        this.ballinfo = new BallInfo();
      }
      if (initObj.hasOwnProperty('obstacleinfo')) {
        this.obstacleinfo = initObj.obstacleinfo
      }
      else {
        this.obstacleinfo = new ObstaclesInfo();
      }
      if (initObj.hasOwnProperty('robotinfo')) {
        this.robotinfo = initObj.robotinfo
      }
      else {
        this.robotinfo = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type OminiVisionInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [ballinfo]
    bufferOffset = BallInfo.serialize(obj.ballinfo, buffer, bufferOffset);
    // Serialize message field [obstacleinfo]
    bufferOffset = ObstaclesInfo.serialize(obj.obstacleinfo, buffer, bufferOffset);
    // Serialize message field [robotinfo]
    // Serialize the length for message field [robotinfo]
    bufferOffset = _serializer.uint32(obj.robotinfo.length, buffer, bufferOffset);
    obj.robotinfo.forEach((val) => {
      bufferOffset = RobotInfo.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type OminiVisionInfo
    let len;
    let data = new OminiVisionInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [ballinfo]
    data.ballinfo = BallInfo.deserialize(buffer, bufferOffset);
    // Deserialize message field [obstacleinfo]
    data.obstacleinfo = ObstaclesInfo.deserialize(buffer, bufferOffset);
    // Deserialize message field [robotinfo]
    // Deserialize array length for message field [robotinfo]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.robotinfo = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.robotinfo[i] = RobotInfo.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += BallInfo.getMessageSize(object.ballinfo);
    length += ObstaclesInfo.getMessageSize(object.obstacleinfo);
    object.robotinfo.forEach((val) => {
      length += RobotInfo.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nubot_common/OminiVisionInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '18b8f1ee8d2b3404355562e6a8b63804';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    BallInfo ballinfo
    
    ObstaclesInfo obstacleinfo
    
    RobotInfo[]  robotinfo
    
    
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    ================================================================================
    MSG: nubot_common/BallInfo
    Header header
    int32     ballinfostate
    Point2d   pos
    PPoint    real_pos
    Point2d   velocity
    bool      pos_known
    bool      velocity_known
    
    
    ================================================================================
    MSG: nubot_common/Point2d
    float32 x
    float32 y
    
    ================================================================================
    MSG: nubot_common/PPoint
    float32 angle
    float32 radius
    
    ================================================================================
    MSG: nubot_common/ObstaclesInfo
    Header header
    Point2d[] pos
    PPoint[] polar_pos
    
    
    ================================================================================
    MSG: nubot_common/RobotInfo
    Header header
    int32    AgentID
    Point2d  pos
    Angle    heading
    float32  vrot
    Point2d  vtrans
    bool     iskick     
    bool     isvalid 
    bool     isstuck 
    bool     isdribble
    char     current_role
    float32  role_time
    Point2d  target
     
    
    ================================================================================
    MSG: nubot_common/Angle
    float32 theta
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new OminiVisionInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.ballinfo !== undefined) {
      resolved.ballinfo = BallInfo.Resolve(msg.ballinfo)
    }
    else {
      resolved.ballinfo = new BallInfo()
    }

    if (msg.obstacleinfo !== undefined) {
      resolved.obstacleinfo = ObstaclesInfo.Resolve(msg.obstacleinfo)
    }
    else {
      resolved.obstacleinfo = new ObstaclesInfo()
    }

    if (msg.robotinfo !== undefined) {
      resolved.robotinfo = new Array(msg.robotinfo.length);
      for (let i = 0; i < resolved.robotinfo.length; ++i) {
        resolved.robotinfo[i] = RobotInfo.Resolve(msg.robotinfo[i]);
      }
    }
    else {
      resolved.robotinfo = []
    }

    return resolved;
    }
};

module.exports = OminiVisionInfo;
