; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude OdoInfo.msg.html

(cl:defclass <OdoInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (Vx
    :reader Vx
    :initarg :Vx
    :type cl:float
    :initform 0.0)
   (Vy
    :reader Vy
    :initarg :Vy
    :type cl:float
    :initform 0.0)
   (w
    :reader w
    :initarg :w
    :type cl:float
    :initform 0.0)
   (RobotStuck
    :reader RobotStuck
    :initarg :RobotStuck
    :type cl:boolean
    :initform cl:nil)
   (PowerState
    :reader PowerState
    :initarg :PowerState
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass OdoInfo (<OdoInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <OdoInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'OdoInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<OdoInfo> is deprecated: use nubot_common-msg:OdoInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <OdoInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:header-val is deprecated.  Use nubot_common-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'Vx-val :lambda-list '(m))
(cl:defmethod Vx-val ((m <OdoInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:Vx-val is deprecated.  Use nubot_common-msg:Vx instead.")
  (Vx m))

(cl:ensure-generic-function 'Vy-val :lambda-list '(m))
(cl:defmethod Vy-val ((m <OdoInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:Vy-val is deprecated.  Use nubot_common-msg:Vy instead.")
  (Vy m))

(cl:ensure-generic-function 'w-val :lambda-list '(m))
(cl:defmethod w-val ((m <OdoInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:w-val is deprecated.  Use nubot_common-msg:w instead.")
  (w m))

(cl:ensure-generic-function 'RobotStuck-val :lambda-list '(m))
(cl:defmethod RobotStuck-val ((m <OdoInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:RobotStuck-val is deprecated.  Use nubot_common-msg:RobotStuck instead.")
  (RobotStuck m))

(cl:ensure-generic-function 'PowerState-val :lambda-list '(m))
(cl:defmethod PowerState-val ((m <OdoInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:PowerState-val is deprecated.  Use nubot_common-msg:PowerState instead.")
  (PowerState m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <OdoInfo>) ostream)
  "Serializes a message object of type '<OdoInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Vx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Vy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'w))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'RobotStuck) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'PowerState) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <OdoInfo>) istream)
  "Deserializes a message object of type '<OdoInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Vx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Vy) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'w) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'RobotStuck) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'PowerState) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<OdoInfo>)))
  "Returns string type for a message object of type '<OdoInfo>"
  "nubot_common/OdoInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'OdoInfo)))
  "Returns string type for a message object of type 'OdoInfo"
  "nubot_common/OdoInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<OdoInfo>)))
  "Returns md5sum for a message object of type '<OdoInfo>"
  "b4f534aa8c080899ef112a410cc2c113")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'OdoInfo)))
  "Returns md5sum for a message object of type 'OdoInfo"
  "b4f534aa8c080899ef112a410cc2c113")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<OdoInfo>)))
  "Returns full string definition for message of type '<OdoInfo>"
  (cl:format cl:nil "Header  header~%float32 Vx~%float32 Vy~%float32 w~%bool    RobotStuck~%bool    PowerState~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'OdoInfo)))
  "Returns full string definition for message of type 'OdoInfo"
  (cl:format cl:nil "Header  header~%float32 Vx~%float32 Vy~%float32 w~%bool    RobotStuck~%bool    PowerState~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <OdoInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <OdoInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'OdoInfo
    (cl:cons ':header (header msg))
    (cl:cons ':Vx (Vx msg))
    (cl:cons ':Vy (Vy msg))
    (cl:cons ':w (w msg))
    (cl:cons ':RobotStuck (RobotStuck msg))
    (cl:cons ':PowerState (PowerState msg))
))
