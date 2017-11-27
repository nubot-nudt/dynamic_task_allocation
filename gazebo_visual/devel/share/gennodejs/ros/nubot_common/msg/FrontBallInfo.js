// Auto-generated. Do not edit!

// (in-package nubot_common.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let PPoint = require('./PPoint.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class FrontBallInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.real_pos = null;
      this.pos_known = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('real_pos')) {
        this.real_pos = initObj.real_pos
      }
      else {
        this.real_pos = new PPoint();
      }
      if (initObj.hasOwnProperty('pos_known')) {
        this.pos_known = initObj.pos_known
      }
      else {
        this.pos_known = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FrontBallInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [real_pos]
    bufferOffset = PPoint.serialize(obj.real_pos, buffer, bufferOffset);
    // Serialize message field [pos_known]
    bufferOffset = _serializer.bool(obj.pos_known, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FrontBallInfo
    let len;
    let data = new FrontBallInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [real_pos]
    data.real_pos = PPoint.deserialize(buffer, bufferOffset);
    // Deserialize message field [pos_known]
    data.pos_known = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 9;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nubot_common/FrontBallInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2f6f5be4b3c5cce090957cd65810f7ac';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    PPoint real_pos
    bool   pos_known
     
    
    
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
    const resolved = new FrontBallInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.real_pos !== undefined) {
      resolved.real_pos = PPoint.Resolve(msg.real_pos)
    }
    else {
      resolved.real_pos = new PPoint()
    }

    if (msg.pos_known !== undefined) {
      resolved.pos_known = msg.pos_known;
    }
    else {
      resolved.pos_known = false
    }

    return resolved;
    }
};

module.exports = FrontBallInfo;
