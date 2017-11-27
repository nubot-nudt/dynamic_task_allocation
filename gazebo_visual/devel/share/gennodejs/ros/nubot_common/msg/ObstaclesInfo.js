// Auto-generated. Do not edit!

// (in-package nubot_common.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Point2d = require('./Point2d.js');
let PPoint = require('./PPoint.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class ObstaclesInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.pos = null;
      this.polar_pos = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('pos')) {
        this.pos = initObj.pos
      }
      else {
        this.pos = [];
      }
      if (initObj.hasOwnProperty('polar_pos')) {
        this.polar_pos = initObj.polar_pos
      }
      else {
        this.polar_pos = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ObstaclesInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [pos]
    // Serialize the length for message field [pos]
    bufferOffset = _serializer.uint32(obj.pos.length, buffer, bufferOffset);
    obj.pos.forEach((val) => {
      bufferOffset = Point2d.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [polar_pos]
    // Serialize the length for message field [polar_pos]
    bufferOffset = _serializer.uint32(obj.polar_pos.length, buffer, bufferOffset);
    obj.polar_pos.forEach((val) => {
      bufferOffset = PPoint.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ObstaclesInfo
    let len;
    let data = new ObstaclesInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [pos]
    // Deserialize array length for message field [pos]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.pos = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.pos[i] = Point2d.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [polar_pos]
    // Deserialize array length for message field [polar_pos]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.polar_pos = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.polar_pos[i] = PPoint.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 8 * object.pos.length;
    length += 8 * object.polar_pos.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nubot_common/ObstaclesInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8850a2241dd98578d2d66d842f5946c8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    Point2d[] pos
    PPoint[] polar_pos
    
    
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
    MSG: nubot_common/Point2d
    float32 x
    float32 y
    
    ================================================================================
    MSG: nubot_common/PPoint
    float32 angle
    float32 radius
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ObstaclesInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.pos !== undefined) {
      resolved.pos = new Array(msg.pos.length);
      for (let i = 0; i < resolved.pos.length; ++i) {
        resolved.pos[i] = Point2d.Resolve(msg.pos[i]);
      }
    }
    else {
      resolved.pos = []
    }

    if (msg.polar_pos !== undefined) {
      resolved.polar_pos = new Array(msg.polar_pos.length);
      for (let i = 0; i < resolved.polar_pos.length; ++i) {
        resolved.polar_pos[i] = PPoint.Resolve(msg.polar_pos[i]);
      }
    }
    else {
      resolved.polar_pos = []
    }

    return resolved;
    }
};

module.exports = ObstaclesInfo;
