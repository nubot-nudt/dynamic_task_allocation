; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude FrontBallInfo.msg.html

(cl:defclass <FrontBallInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (real_pos
    :reader real_pos
    :initarg :real_pos
    :type nubot_common-msg:PPoint
    :initform (cl:make-instance 'nubot_common-msg:PPoint))
   (pos_known
    :reader pos_known
    :initarg :pos_known
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass FrontBallInfo (<FrontBallInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FrontBallInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FrontBallInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<FrontBallInfo> is deprecated: use nubot_common-msg:FrontBallInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <FrontBallInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:header-val is deprecated.  Use nubot_common-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'real_pos-val :lambda-list '(m))
(cl:defmethod real_pos-val ((m <FrontBallInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:real_pos-val is deprecated.  Use nubot_common-msg:real_pos instead.")
  (real_pos m))

(cl:ensure-generic-function 'pos_known-val :lambda-list '(m))
(cl:defmethod pos_known-val ((m <FrontBallInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pos_known-val is deprecated.  Use nubot_common-msg:pos_known instead.")
  (pos_known m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FrontBallInfo>) ostream)
  "Serializes a message object of type '<FrontBallInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'real_pos) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'pos_known) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FrontBallInfo>) istream)
  "Deserializes a message object of type '<FrontBallInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'real_pos) istream)
    (cl:setf (cl:slot-value msg 'pos_known) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FrontBallInfo>)))
  "Returns string type for a message object of type '<FrontBallInfo>"
  "nubot_common/FrontBallInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FrontBallInfo)))
  "Returns string type for a message object of type 'FrontBallInfo"
  "nubot_common/FrontBallInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FrontBallInfo>)))
  "Returns md5sum for a message object of type '<FrontBallInfo>"
  "2f6f5be4b3c5cce090957cd65810f7ac")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FrontBallInfo)))
  "Returns md5sum for a message object of type 'FrontBallInfo"
  "2f6f5be4b3c5cce090957cd65810f7ac")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FrontBallInfo>)))
  "Returns full string definition for message of type '<FrontBallInfo>"
  (cl:format cl:nil "Header header~%PPoint real_pos~%bool   pos_known~% ~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/PPoint~%float32 angle~%float32 radius~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FrontBallInfo)))
  "Returns full string definition for message of type 'FrontBallInfo"
  (cl:format cl:nil "Header header~%PPoint real_pos~%bool   pos_known~% ~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/PPoint~%float32 angle~%float32 radius~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FrontBallInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'real_pos))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FrontBallInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'FrontBallInfo
    (cl:cons ':header (header msg))
    (cl:cons ':real_pos (real_pos msg))
    (cl:cons ':pos_known (pos_known msg))
))
