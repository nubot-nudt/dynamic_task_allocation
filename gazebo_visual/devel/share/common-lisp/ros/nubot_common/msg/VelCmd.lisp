; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude VelCmd.msg.html

(cl:defclass <VelCmd> (roslisp-msg-protocol:ros-message)
  ((Vx
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
    :initform 0.0))
)

(cl:defclass VelCmd (<VelCmd>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VelCmd>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VelCmd)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<VelCmd> is deprecated: use nubot_common-msg:VelCmd instead.")))

(cl:ensure-generic-function 'Vx-val :lambda-list '(m))
(cl:defmethod Vx-val ((m <VelCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:Vx-val is deprecated.  Use nubot_common-msg:Vx instead.")
  (Vx m))

(cl:ensure-generic-function 'Vy-val :lambda-list '(m))
(cl:defmethod Vy-val ((m <VelCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:Vy-val is deprecated.  Use nubot_common-msg:Vy instead.")
  (Vy m))

(cl:ensure-generic-function 'w-val :lambda-list '(m))
(cl:defmethod w-val ((m <VelCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:w-val is deprecated.  Use nubot_common-msg:w instead.")
  (w m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VelCmd>) ostream)
  "Serializes a message object of type '<VelCmd>"
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
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VelCmd>) istream)
  "Deserializes a message object of type '<VelCmd>"
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
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VelCmd>)))
  "Returns string type for a message object of type '<VelCmd>"
  "nubot_common/VelCmd")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VelCmd)))
  "Returns string type for a message object of type 'VelCmd"
  "nubot_common/VelCmd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VelCmd>)))
  "Returns md5sum for a message object of type '<VelCmd>"
  "914217797e9c6227112d1ec2a4b462eb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VelCmd)))
  "Returns md5sum for a message object of type 'VelCmd"
  "914217797e9c6227112d1ec2a4b462eb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VelCmd>)))
  "Returns full string definition for message of type '<VelCmd>"
  (cl:format cl:nil "float32 Vx~%float32 Vy~%float32 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VelCmd)))
  "Returns full string definition for message of type 'VelCmd"
  (cl:format cl:nil "float32 Vx~%float32 Vy~%float32 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VelCmd>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VelCmd>))
  "Converts a ROS message object to a list"
  (cl:list 'VelCmd
    (cl:cons ':Vx (Vx msg))
    (cl:cons ':Vy (Vy msg))
    (cl:cons ':w (w msg))
))
