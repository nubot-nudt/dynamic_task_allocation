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

class CoachInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.MatchMode = null;
      this.MatchType = null;
      this.TestMode = null;
      this.pointA = null;
      this.pointB = null;
      this.angleA = null;
      this.angleB = null;
      this.idA = null;
      this.idB = null;
      this.kickforce = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('MatchMode')) {
        this.MatchMode = initObj.MatchMode
      }
      else {
        this.MatchMode = 0;
      }
      if (initObj.hasOwnProperty('MatchType')) {
        this.MatchType = initObj.MatchType
      }
      else {
        this.MatchType = 0;
      }
      if (initObj.hasOwnProperty('TestMode')) {
        this.TestMode = initObj.TestMode
      }
      else {
        this.TestMode = 0;
      }
      if (initObj.hasOwnProperty('pointA')) {
        this.pointA = initObj.pointA
      }
      else {
        this.pointA = new Point2d();
      }
      if (initObj.hasOwnProperty('pointB')) {
        this.pointB = initObj.pointB
      }
      else {
        this.pointB = new Point2d();
      }
      if (initObj.hasOwnProperty('angleA')) {
        this.angleA = initObj.angleA
      }
      else {
        this.angleA = 0;
      }
      if (initObj.hasOwnProperty('angleB')) {
        this.angleB = initObj.angleB
      }
      else {
        this.angleB = 0;
      }
      if (initObj.hasOwnProperty('idA')) {
        this.idA = initObj.idA
      }
      else {
        this.idA = 0;
      }
      if (initObj.hasOwnProperty('idB')) {
        this.idB = initObj.idB
      }
      else {
        this.idB = 0;
      }
      if (initObj.hasOwnProperty('kickforce')) {
        this.kickforce = initObj.kickforce
      }
      else {
        this.kickforce = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CoachInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [MatchMode]
    bufferOffset = _serializer.char(obj.MatchMode, buffer, bufferOffset);
    // Serialize message field [MatchType]
    bufferOffset = _serializer.char(obj.MatchType, buffer, bufferOffset);
    // Serialize message field [TestMode]
    bufferOffset = _serializer.char(obj.TestMode, buffer, bufferOffset);
    // Serialize message field [pointA]
    bufferOffset = Point2d.serialize(obj.pointA, buffer, bufferOffset);
    // Serialize message field [pointB]
    bufferOffset = Point2d.serialize(obj.pointB, buffer, bufferOffset);
    // Serialize message field [angleA]
    bufferOffset = _serializer.int16(obj.angleA, buffer, bufferOffset);
    // Serialize message field [angleB]
    bufferOffset = _serializer.int16(obj.angleB, buffer, bufferOffset);
    // Serialize message field [idA]
    bufferOffset = _serializer.char(obj.idA, buffer, bufferOffset);
    // Serialize message field [idB]
    bufferOffset = _serializer.char(obj.idB, buffer, bufferOffset);
    // Serialize message field [kickforce]
    bufferOffset = _serializer.char(obj.kickforce, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CoachInfo
    let len;
    let data = new CoachInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [MatchMode]
    data.MatchMode = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [MatchType]
    data.MatchType = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [TestMode]
    data.TestMode = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [pointA]
    data.pointA = Point2d.deserialize(buffer, bufferOffset);
    // Deserialize message field [pointB]
    data.pointB = Point2d.deserialize(buffer, bufferOffset);
    // Deserialize message field [angleA]
    data.angleA = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [angleB]
    data.angleB = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [idA]
    data.idA = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [idB]
    data.idB = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [kickforce]
    data.kickforce = _deserializer.char(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 26;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nubot_common/CoachInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7bb01a0f4328cb28beb61d4f502c2969';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    char MatchMode
    char MatchType
    char TestMode           
    Point2d pointA
    Point2d pointB
    int16 angleA
    int16 angleB
    char idA
    char idB
    char kickforce
    
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
    const resolved = new CoachInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.MatchMode !== undefined) {
      resolved.MatchMode = msg.MatchMode;
    }
    else {
      resolved.MatchMode = 0
    }

    if (msg.MatchType !== undefined) {
      resolved.MatchType = msg.MatchType;
    }
    else {
      resolved.MatchType = 0
    }

    if (msg.TestMode !== undefined) {
      resolved.TestMode = msg.TestMode;
    }
    else {
      resolved.TestMode = 0
    }

    if (msg.pointA !== undefined) {
      resolved.pointA = Point2d.Resolve(msg.pointA)
    }
    else {
      resolved.pointA = new Point2d()
    }

    if (msg.pointB !== undefined) {
      resolved.pointB = Point2d.Resolve(msg.pointB)
    }
    else {
      resolved.pointB = new Point2d()
    }

    if (msg.angleA !== undefined) {
      resolved.angleA = msg.angleA;
    }
    else {
      resolved.angleA = 0
    }

    if (msg.angleB !== undefined) {
      resolved.angleB = msg.angleB;
    }
    else {
      resolved.angleB = 0
    }

    if (msg.idA !== undefined) {
      resolved.idA = msg.idA;
    }
    else {
      resolved.idA = 0
    }

    if (msg.idB !== undefined) {
      resolved.idB = msg.idB;
    }
    else {
      resolved.idB = 0
    }

    if (msg.kickforce !== undefined) {
      resolved.kickforce = msg.kickforce;
    }
    else {
      resolved.kickforce = 0
    }

    return resolved;
    }
};

module.exports = CoachInfo;
