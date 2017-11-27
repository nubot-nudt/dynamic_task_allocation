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
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class TargetInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.target = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('target')) {
        this.target = initObj.target
      }
      else {
        this.target = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type TargetInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [target]
    // Serialize the length for message field [target]
    bufferOffset = _serializer.uint32(obj.target.length, buffer, bufferOffset);
    obj.target.forEach((val) => {
      bufferOffset = Point2d.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type TargetInfo
    let len;
    let data = new TargetInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [target]
    // Deserialize array length for message field [target]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.target = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.target[i] = Point2d.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 8 * object.target.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nubot_common/TargetInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a4938944832bdc9277041fe2fa758dce';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    Point2d[] target
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new TargetInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.target !== undefined) {
      resolved.target = new Array(msg.target.length);
      for (let i = 0; i < resolved.target.length; ++i) {
        resolved.target[i] = Point2d.Resolve(msg.target[i]);
      }
    }
    else {
      resolved.target = []
    }

    return resolved;
    }
};

module.exports = TargetInfo;
