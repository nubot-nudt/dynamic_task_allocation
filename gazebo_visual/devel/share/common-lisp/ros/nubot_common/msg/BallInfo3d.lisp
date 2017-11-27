; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude BallInfo3d.msg.html

(cl:defclass <BallInfo3d> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (pos
    :reader pos
    :initarg :pos
    :type nubot_common-msg:Point3d
    :initform (cl:make-instance 'nubot_common-msg:Point3d))
   (velocity
    :reader velocity
    :initarg :velocity
    :type nubot_common-msg:Point3d
    :initform (cl:make-instance 'nubot_common-msg:Point3d))
   (pos_known_3d
    :reader pos_known_3d
    :initarg :pos_known_3d
    :type cl:boolean
    :initform cl:nil)
   (pos_known_2d
    :reader pos_known_2d
    :initarg :pos_known_2d
    :type cl:boolean
    :initform cl:nil)
   (velocity_known
    :reader velocity_known
    :initarg :velocity_known
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass BallInfo3d (<BallInfo3d>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BallInfo3d>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BallInfo3d)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<BallInfo3d> is deprecated: use nubot_common-msg:BallInfo3d instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <BallInfo3d>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:header-val is deprecated.  Use nubot_common-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'pos-val :lambda-list '(m))
(cl:defmethod pos-val ((m <BallInfo3d>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pos-val is deprecated.  Use nubot_common-msg:pos instead.")
  (pos m))

(cl:ensure-generic-function 'velocity-val :lambda-list '(m))
(cl:defmethod velocity-val ((m <BallInfo3d>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:velocity-val is deprecated.  Use nubot_common-msg:velocity instead.")
  (velocity m))

(cl:ensure-generic-function 'pos_known_3d-val :lambda-list '(m))
(cl:defmethod pos_known_3d-val ((m <BallInfo3d>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pos_known_3d-val is deprecated.  Use nubot_common-msg:pos_known_3d instead.")
  (pos_known_3d m))

(cl:ensure-generic-function 'pos_known_2d-val :lambda-list '(m))
(cl:defmethod pos_known_2d-val ((m <BallInfo3d>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pos_known_2d-val is deprecated.  Use nubot_common-msg:pos_known_2d instead.")
  (pos_known_2d m))

(cl:ensure-generic-function 'velocity_known-val :lambda-list '(m))
(cl:defmethod velocity_known-val ((m <BallInfo3d>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:velocity_known-val is deprecated.  Use nubot_common-msg:velocity_known instead.")
  (velocity_known m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BallInfo3d>) ostream)
  "Serializes a message object of type '<BallInfo3d>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pos) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'velocity) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'pos_known_3d) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'pos_known_2d) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'velocity_known) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BallInfo3d>) istream)
  "Deserializes a message object of type '<BallInfo3d>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pos) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'velocity) istream)
    (cl:setf (cl:slot-value msg 'pos_known_3d) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'pos_known_2d) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'velocity_known) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BallInfo3d>)))
  "Returns string type for a message object of type '<BallInfo3d>"
  "nubot_common/BallInfo3d")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BallInfo3d)))
  "Returns string type for a message object of type 'BallInfo3d"
  "nubot_common/BallInfo3d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BallInfo3d>)))
  "Returns md5sum for a message object of type '<BallInfo3d>"
  "6634a529c2fba000f06cf99f5ab31312")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BallInfo3d)))
  "Returns md5sum for a message object of type 'BallInfo3d"
  "6634a529c2fba000f06cf99f5ab31312")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BallInfo3d>)))
  "Returns full string definition for message of type '<BallInfo3d>"
  (cl:format cl:nil "Header header~%Point3d   pos~%Point3d   velocity~%bool      pos_known_3d~%bool      pos_known_2d~%bool      velocity_known~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point3d~%float32 x~%float32 y~%float32 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BallInfo3d)))
  "Returns full string definition for message of type 'BallInfo3d"
  (cl:format cl:nil "Header header~%Point3d   pos~%Point3d   velocity~%bool      pos_known_3d~%bool      pos_known_2d~%bool      velocity_known~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point3d~%float32 x~%float32 y~%float32 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BallInfo3d>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pos))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'velocity))
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BallInfo3d>))
  "Converts a ROS message object to a list"
  (cl:list 'BallInfo3d
    (cl:cons ':header (header msg))
    (cl:cons ':pos (pos msg))
    (cl:cons ':velocity (velocity msg))
    (cl:cons ':pos_known_3d (pos_known_3d msg))
    (cl:cons ':pos_known_2d (pos_known_2d msg))
    (cl:cons ':velocity_known (velocity_known msg))
))
