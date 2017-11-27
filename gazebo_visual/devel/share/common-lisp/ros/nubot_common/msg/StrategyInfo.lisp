; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude StrategyInfo.msg.html

(cl:defclass <StrategyInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (AgentID
    :reader AgentID
    :initarg :AgentID
    :type cl:integer
    :initform 0)
   (targetNum1
    :reader targetNum1
    :initarg :targetNum1
    :type cl:integer
    :initform 0)
   (targetNum2
    :reader targetNum2
    :initarg :targetNum2
    :type cl:integer
    :initform 0)
   (targetNum3
    :reader targetNum3
    :initarg :targetNum3
    :type cl:integer
    :initform 0)
   (targetNum4
    :reader targetNum4
    :initarg :targetNum4
    :type cl:integer
    :initform 0)
   (staticpassNum
    :reader staticpassNum
    :initarg :staticpassNum
    :type cl:integer
    :initform 0)
   (staticcatchNum
    :reader staticcatchNum
    :initarg :staticcatchNum
    :type cl:integer
    :initform 0)
   (role
    :reader role
    :initarg :role
    :type cl:integer
    :initform 0)
   (action
    :reader action
    :initarg :action
    :type cl:integer
    :initform 0)
   (is_dribble
    :reader is_dribble
    :initarg :is_dribble
    :type cl:boolean
    :initform cl:nil)
   (is_kickoff
    :reader is_kickoff
    :initarg :is_kickoff
    :type cl:boolean
    :initform cl:nil)
   (role_time
    :reader role_time
    :initarg :role_time
    :type cl:float
    :initform 0.0)
   (pass_cmd
    :reader pass_cmd
    :initarg :pass_cmd
    :type nubot_common-msg:PassCommands
    :initform (cl:make-instance 'nubot_common-msg:PassCommands)))
)

(cl:defclass StrategyInfo (<StrategyInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StrategyInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StrategyInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<StrategyInfo> is deprecated: use nubot_common-msg:StrategyInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:header-val is deprecated.  Use nubot_common-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'AgentID-val :lambda-list '(m))
(cl:defmethod AgentID-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:AgentID-val is deprecated.  Use nubot_common-msg:AgentID instead.")
  (AgentID m))

(cl:ensure-generic-function 'targetNum1-val :lambda-list '(m))
(cl:defmethod targetNum1-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:targetNum1-val is deprecated.  Use nubot_common-msg:targetNum1 instead.")
  (targetNum1 m))

(cl:ensure-generic-function 'targetNum2-val :lambda-list '(m))
(cl:defmethod targetNum2-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:targetNum2-val is deprecated.  Use nubot_common-msg:targetNum2 instead.")
  (targetNum2 m))

(cl:ensure-generic-function 'targetNum3-val :lambda-list '(m))
(cl:defmethod targetNum3-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:targetNum3-val is deprecated.  Use nubot_common-msg:targetNum3 instead.")
  (targetNum3 m))

(cl:ensure-generic-function 'targetNum4-val :lambda-list '(m))
(cl:defmethod targetNum4-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:targetNum4-val is deprecated.  Use nubot_common-msg:targetNum4 instead.")
  (targetNum4 m))

(cl:ensure-generic-function 'staticpassNum-val :lambda-list '(m))
(cl:defmethod staticpassNum-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:staticpassNum-val is deprecated.  Use nubot_common-msg:staticpassNum instead.")
  (staticpassNum m))

(cl:ensure-generic-function 'staticcatchNum-val :lambda-list '(m))
(cl:defmethod staticcatchNum-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:staticcatchNum-val is deprecated.  Use nubot_common-msg:staticcatchNum instead.")
  (staticcatchNum m))

(cl:ensure-generic-function 'role-val :lambda-list '(m))
(cl:defmethod role-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:role-val is deprecated.  Use nubot_common-msg:role instead.")
  (role m))

(cl:ensure-generic-function 'action-val :lambda-list '(m))
(cl:defmethod action-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:action-val is deprecated.  Use nubot_common-msg:action instead.")
  (action m))

(cl:ensure-generic-function 'is_dribble-val :lambda-list '(m))
(cl:defmethod is_dribble-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:is_dribble-val is deprecated.  Use nubot_common-msg:is_dribble instead.")
  (is_dribble m))

(cl:ensure-generic-function 'is_kickoff-val :lambda-list '(m))
(cl:defmethod is_kickoff-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:is_kickoff-val is deprecated.  Use nubot_common-msg:is_kickoff instead.")
  (is_kickoff m))

(cl:ensure-generic-function 'role_time-val :lambda-list '(m))
(cl:defmethod role_time-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:role_time-val is deprecated.  Use nubot_common-msg:role_time instead.")
  (role_time m))

(cl:ensure-generic-function 'pass_cmd-val :lambda-list '(m))
(cl:defmethod pass_cmd-val ((m <StrategyInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pass_cmd-val is deprecated.  Use nubot_common-msg:pass_cmd instead.")
  (pass_cmd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StrategyInfo>) ostream)
  "Serializes a message object of type '<StrategyInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'AgentID)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'targetNum1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'targetNum2)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'targetNum3)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'targetNum4)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'staticpassNum)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'staticcatchNum)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'role)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'role)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'role)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'role)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'action)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'action)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'action)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'action)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_dribble) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_kickoff) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'role_time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pass_cmd) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StrategyInfo>) istream)
  "Deserializes a message object of type '<StrategyInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'AgentID) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'targetNum1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'targetNum2) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'targetNum3) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'targetNum4) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'staticpassNum) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'staticcatchNum) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'role)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'role)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'role)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'role)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'action)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'action)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'action)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'action)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'is_dribble) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'is_kickoff) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'role_time) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pass_cmd) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StrategyInfo>)))
  "Returns string type for a message object of type '<StrategyInfo>"
  "nubot_common/StrategyInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StrategyInfo)))
  "Returns string type for a message object of type 'StrategyInfo"
  "nubot_common/StrategyInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StrategyInfo>)))
  "Returns md5sum for a message object of type '<StrategyInfo>"
  "9983cea3e357670f055f12d4322a06c9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StrategyInfo)))
  "Returns md5sum for a message object of type 'StrategyInfo"
  "9983cea3e357670f055f12d4322a06c9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StrategyInfo>)))
  "Returns full string definition for message of type '<StrategyInfo>"
  (cl:format cl:nil "Header   header~%int32    AgentID~%int32    targetNum1~%int32    targetNum2~%int32    targetNum3~%int32    targetNum4~%int32    staticpassNum~%int32    staticcatchNum~%uint32   role~%uint32   action~%bool     is_dribble~%bool     is_kickoff~%float32  role_time~%PassCommands  pass_cmd~%~%~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/PassCommands~%uint32  pass_id~%uint32  catch_id~%Point2d pass_pt~%Point2d catch_pt~%bool    is_passout~%bool    is_dynamic_pass~%bool    is_static_pass~%bool    is_valid~% ~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StrategyInfo)))
  "Returns full string definition for message of type 'StrategyInfo"
  (cl:format cl:nil "Header   header~%int32    AgentID~%int32    targetNum1~%int32    targetNum2~%int32    targetNum3~%int32    targetNum4~%int32    staticpassNum~%int32    staticcatchNum~%uint32   role~%uint32   action~%bool     is_dribble~%bool     is_kickoff~%float32  role_time~%PassCommands  pass_cmd~%~%~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/PassCommands~%uint32  pass_id~%uint32  catch_id~%Point2d pass_pt~%Point2d catch_pt~%bool    is_passout~%bool    is_dynamic_pass~%bool    is_static_pass~%bool    is_valid~% ~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StrategyInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4
     4
     4
     4
     4
     4
     1
     1
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pass_cmd))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StrategyInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'StrategyInfo
    (cl:cons ':header (header msg))
    (cl:cons ':AgentID (AgentID msg))
    (cl:cons ':targetNum1 (targetNum1 msg))
    (cl:cons ':targetNum2 (targetNum2 msg))
    (cl:cons ':targetNum3 (targetNum3 msg))
    (cl:cons ':targetNum4 (targetNum4 msg))
    (cl:cons ':staticpassNum (staticpassNum msg))
    (cl:cons ':staticcatchNum (staticcatchNum msg))
    (cl:cons ':role (role msg))
    (cl:cons ':action (action msg))
    (cl:cons ':is_dribble (is_dribble msg))
    (cl:cons ':is_kickoff (is_kickoff msg))
    (cl:cons ':role_time (role_time msg))
    (cl:cons ':pass_cmd (pass_cmd msg))
))
