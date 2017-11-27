; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude BallInfo.msg.html

(cl:defclass <BallInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (ballinfostate
    :reader ballinfostate
    :initarg :ballinfostate
    :type cl:integer
    :initform 0)
   (pos
    :reader pos
    :initarg :pos
    :type nubot_common-msg:Point2d
    :initform (cl:make-instance 'nubot_common-msg:Point2d))
   (real_pos
    :reader real_pos
    :initarg :real_pos
    :type nubot_common-msg:PPoint
    :initform (cl:make-instance 'nubot_common-msg:PPoint))
   (velocity
    :reader velocity
    :initarg :velocity
    :type nubot_common-msg:Point2d
    :initform (cl:make-instance 'nubot_common-msg:Point2d))
   (pos_known
    :reader pos_known
    :initarg :pos_known
    :type cl:boolean
    :initform cl:nil)
   (velocity_known
    :reader velocity_known
    :initarg :velocity_known
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass BallInfo (<BallInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BallInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BallInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<BallInfo> is deprecated: use nubot_common-msg:BallInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <BallInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:header-val is deprecated.  Use nubot_common-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'ballinfostate-val :lambda-list '(m))
(cl:defmethod ballinfostate-val ((m <BallInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:ballinfostate-val is deprecated.  Use nubot_common-msg:ballinfostate instead.")
  (ballinfostate m))

(cl:ensure-generic-function 'pos-val :lambda-list '(m))
(cl:defmethod pos-val ((m <BallInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pos-val is deprecated.  Use nubot_common-msg:pos instead.")
  (pos m))

(cl:ensure-generic-function 'real_pos-val :lambda-list '(m))
(cl:defmethod real_pos-val ((m <BallInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:real_pos-val is deprecated.  Use nubot_common-msg:real_pos instead.")
  (real_pos m))

(cl:ensure-generic-function 'velocity-val :lambda-list '(m))
(cl:defmethod velocity-val ((m <BallInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:velocity-val is deprecated.  Use nubot_common-msg:velocity instead.")
  (velocity m))

(cl:ensure-generic-function 'pos_known-val :lambda-list '(m))
(cl:defmethod pos_known-val ((m <BallInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pos_known-val is deprecated.  Use nubot_common-msg:pos_known instead.")
  (pos_known m))

(cl:ensure-generic-function 'velocity_known-val :lambda-list '(m))
(cl:defmethod velocity_known-val ((m <BallInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:velocity_known-val is deprecated.  Use nubot_common-msg:velocity_known instead.")
  (velocity_known m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BallInfo>) ostream)
  "Serializes a message object of type '<BallInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'ballinfostate)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pos) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'real_pos) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'velocity) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'pos_known) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'velocity_known) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BallInfo>) istream)
  "Deserializes a message object of type '<BallInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ballinfostate) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pos) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'real_pos) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'velocity) istream)
    (cl:setf (cl:slot-value msg 'pos_known) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'velocity_known) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BallInfo>)))
  "Returns string type for a message object of type '<BallInfo>"
  "nubot_common/BallInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BallInfo)))
  "Returns string type for a message object of type 'BallInfo"
  "nubot_common/BallInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BallInfo>)))
  "Returns md5sum for a message object of type '<BallInfo>"
  "06211c2a8d639c68390f487a28e6a33a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BallInfo)))
  "Returns md5sum for a message object of type 'BallInfo"
  "06211c2a8d639c68390f487a28e6a33a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BallInfo>)))
  "Returns full string definition for message of type '<BallInfo>"
  (cl:format cl:nil "Header header~%int32     ballinfostate~%Point2d   pos~%PPoint    real_pos~%Point2d   velocity~%bool      pos_known~%bool      velocity_known~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%================================================================================~%MSG: nubot_common/PPoint~%float32 angle~%float32 radius~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BallInfo)))
  "Returns full string definition for message of type 'BallInfo"
  (cl:format cl:nil "Header header~%int32     ballinfostate~%Point2d   pos~%PPoint    real_pos~%Point2d   velocity~%bool      pos_known~%bool      velocity_known~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%================================================================================~%MSG: nubot_common/PPoint~%float32 angle~%float32 radius~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BallInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pos))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'real_pos))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'velocity))
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BallInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'BallInfo
    (cl:cons ':header (header msg))
    (cl:cons ':ballinfostate (ballinfostate msg))
    (cl:cons ':pos (pos msg))
    (cl:cons ':real_pos (real_pos msg))
    (cl:cons ':velocity (velocity msg))
    (cl:cons ':pos_known (pos_known msg))
    (cl:cons ':velocity_known (velocity_known msg))
))
