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

class BallHandleRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.enable = null;
    }
    else {
      if (initObj.hasOwnProperty('enable')) {
        this.enable = initObj.enable
      }
      else {
        this.enable = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BallHandleRequest
    // Serialize message field [enable]
    bufferOffset = _serializer.int64(obj.enable, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BallHandleRequest
    let len;
    let data = new BallHandleRequest(null);
    // Deserialize message field [enable]
    data.enable = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'nubot_common/BallHandleRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c72133dd88f3c751f622755eeb9383c7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 enable
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BallHandleRequest(null);
    if (msg.enable !== undefined) {
      resolved.enable = msg.enable;
    }
    else {
      resolved.enable = 0
    }

    return resolved;
    }
};

class BallHandleResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.BallIsHolding = null;
    }
    else {
      if (initObj.hasOwnProperty('BallIsHolding')) {
        this.BallIsHolding = initObj.BallIsHolding
      }
      else {
        this.BallIsHolding = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BallHandleResponse
    // Serialize message field [BallIsHolding]
    bufferOffset = _serializer.int64(obj.BallIsHolding, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BallHandleResponse
    let len;
    let data = new BallHandleResponse(null);
    // Deserialize message field [BallIsHolding]
    data.BallIsHolding = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'nubot_common/BallHandleResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '371e9ec4fdab9c30277b932f121cf460';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 BallIsHolding
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BallHandleResponse(null);
    if (msg.BallIsHolding !== undefined) {
      resolved.BallIsHolding = msg.BallIsHolding;
    }
    else {
      resolved.BallIsHolding = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: BallHandleRequest,
  Response: BallHandleResponse,
  md5sum() { return 'f352f0080766880a151542e750a50ea8'; },
  datatype() { return 'nubot_common/BallHandle'; }
};
