// Auto-generated. Do not edit!

// (in-package nubot_common.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class ShootRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.strength = null;
      this.ShootPos = null;
    }
    else {
      if (initObj.hasOwnProperty('strength')) {
        this.strength = initObj.strength
      }
      else {
        this.strength = 0.0;
      }
      if (initObj.hasOwnProperty('ShootPos')) {
        this.ShootPos = initObj.ShootPos
      }
      else {
        this.ShootPos = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ShootRequest
    // Serialize message field [strength]
    bufferOffset = _serializer.float32(obj.strength, buffer, bufferOffset);
    // Serialize message field [ShootPos]
    bufferOffset = _serializer.int64(obj.ShootPos, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ShootRequest
    let len;
    let data = new ShootRequest(null);
    // Deserialize message field [strength]
    data.strength = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ShootPos]
    data.ShootPos = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a service object
    return 'nubot_common/ShootRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3198871bad21e7a959f16b2e8430d374';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 strength
    int64 ShootPos
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ShootRequest(null);
    if (msg.strength !== undefined) {
      resolved.strength = msg.strength;
    }
    else {
      resolved.strength = 0.0
    }

    if (msg.ShootPos !== undefined) {
      resolved.ShootPos = msg.ShootPos;
    }
    else {
      resolved.ShootPos = 0
    }

    return resolved;
    }
};

class ShootResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ShootIsDone = null;
    }
    else {
      if (initObj.hasOwnProperty('ShootIsDone')) {
        this.ShootIsDone = initObj.ShootIsDone
      }
      else {
        this.ShootIsDone = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ShootResponse
    // Serialize message field [ShootIsDone]
    bufferOffset = _serializer.int64(obj.ShootIsDone, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ShootResponse
    let len;
    let data = new ShootResponse(null);
    // Deserialize message field [ShootIsDone]
    data.ShootIsDone = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'nubot_common/ShootResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '942dc5d9ce09e09747b9618619df0e71';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 ShootIsDone
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ShootResponse(null);
    if (msg.ShootIsDone !== undefined) {
      resolved.ShootIsDone = msg.ShootIsDone;
    }
    else {
      resolved.ShootIsDone = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: ShootRequest,
  Response: ShootResponse,
  md5sum() { return '5f7b2fca861afe65dc92d3f6a153bbec'; },
  datatype() { return 'nubot_common/Shoot'; }
};
