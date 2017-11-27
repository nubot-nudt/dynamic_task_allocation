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

//-----------------------------------------------------------

class PassCommands {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.pass_id = null;
      this.catch_id = null;
      this.pass_pt = null;
      this.catch_pt = null;
      this.is_passout = null;
      this.is_dynamic_pass = null;
      this.is_static_pass = null;
      this.is_valid = null;
    }
    else {
      if (initObj.hasOwnProperty('pass_id')) {
        this.pass_id = initObj.pass_id
      }
      else {
        this.pass_id = 0;
      }
      if (initObj.hasOwnProperty('catch_id')) {
        this.catch_id = initObj.catch_id
      }
      else {
        this.catch_id = 0;
      }
      if (initObj.hasOwnProperty('pass_pt')) {
        this.pass_pt = initObj.pass_pt
      }
      else {
        this.pass_pt = new Point2d();
      }
      if (initObj.hasOwnProperty('catch_pt')) {
        this.catch_pt = initObj.catch_pt
      }
      else {
        this.catch_pt = new Point2d();
      }
      if (initObj.hasOwnProperty('is_passout')) {
        this.is_passout = initObj.is_passout
      }
      else {
        this.is_passout = false;
      }
      if (initObj.hasOwnProperty('is_dynamic_pass')) {
        this.is_dynamic_pass = initObj.is_dynamic_pass
      }
      else {
        this.is_dynamic_pass = false;
      }
      if (initObj.hasOwnProperty('is_static_pass')) {
        this.is_static_pass = initObj.is_static_pass
      }
      else {
        this.is_static_pass = false;
      }
      if (initObj.hasOwnProperty('is_valid')) {
        this.is_valid = initObj.is_valid
      }
      else {
        this.is_valid = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PassCommands
    // Serialize message field [pass_id]
    bufferOffset = _serializer.uint32(obj.pass_id, buffer, bufferOffset);
    // Serialize message field [catch_id]
    bufferOffset = _serializer.uint32(obj.catch_id, buffer, bufferOffset);
    // Serialize message field [pass_pt]
    bufferOffset = Point2d.serialize(obj.pass_pt, buffer, bufferOffset);
    // Serialize message field [catch_pt]
    bufferOffset = Point2d.serialize(obj.catch_pt, buffer, bufferOffset);
    // Serialize message field [is_passout]
    bufferOffset = _serializer.bool(obj.is_passout, buffer, bufferOffset);
    // Serialize message field [is_dynamic_pass]
    bufferOffset = _serializer.bool(obj.is_dynamic_pass, buffer, bufferOffset);
    // Serialize message field [is_static_pass]
    bufferOffset = _serializer.bool(obj.is_static_pass, buffer, bufferOffset);
    // Serialize message field [is_valid]
    bufferOffset = _serializer.bool(obj.is_valid, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PassCommands
    let len;
    let data = new PassCommands(null);
    // Deserialize message field [pass_id]
    data.pass_id = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [catch_id]
    data.catch_id = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [pass_pt]
    data.pass_pt = Point2d.deserialize(buffer, bufferOffset);
    // Deserialize message field [catch_pt]
    data.catch_pt = Point2d.deserialize(buffer, bufferOffset);
    // Deserialize message field [is_passout]
    data.is_passout = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [is_dynamic_pass]
    data.is_dynamic_pass = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [is_static_pass]
    data.is_static_pass = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [is_valid]
    data.is_valid = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 28;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nubot_common/PassCommands';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd50d66ad0a96e8d9eae8a7a9da579ad2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint32  pass_id
    uint32  catch_id
    Point2d pass_pt
    Point2d catch_pt
    bool    is_passout
    bool    is_dynamic_pass
    bool    is_static_pass
    bool    is_valid
     
    
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
    const resolved = new PassCommands(null);
    if (msg.pass_id !== undefined) {
      resolved.pass_id = msg.pass_id;
    }
    else {
      resolved.pass_id = 0
    }

    if (msg.catch_id !== undefined) {
      resolved.catch_id = msg.catch_id;
    }
    else {
      resolved.catch_id = 0
    }

    if (msg.pass_pt !== undefined) {
      resolved.pass_pt = Point2d.Resolve(msg.pass_pt)
    }
    else {
      resolved.pass_pt = new Point2d()
    }

    if (msg.catch_pt !== undefined) {
      resolved.catch_pt = Point2d.Resolve(msg.catch_pt)
    }
    else {
      resolved.catch_pt = new Point2d()
    }

    if (msg.is_passout !== undefined) {
      resolved.is_passout = msg.is_passout;
    }
    else {
      resolved.is_passout = false
    }

    if (msg.is_dynamic_pass !== undefined) {
      resolved.is_dynamic_pass = msg.is_dynamic_pass;
    }
    else {
      resolved.is_dynamic_pass = false
    }

    if (msg.is_static_pass !== undefined) {
      resolved.is_static_pass = msg.is_static_pass;
    }
    else {
      resolved.is_static_pass = false
    }

    if (msg.is_valid !== undefined) {
      resolved.is_valid = msg.is_valid;
    }
    else {
      resolved.is_valid = false
    }

    return resolved;
    }
};

module.exports = PassCommands;
