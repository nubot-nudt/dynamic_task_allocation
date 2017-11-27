; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude Point2d.msg.html

(cl:defclass <Point2d> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0))
)

(cl:defclass Point2d (<Point2d>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Point2d>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Point2d)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<Point2d> is deprecated: use nubot_common-msg:Point2d instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <Point2d>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:x-val is deprecated.  Use nubot_common-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <Point2d>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:y-val is deprecated.  Use nubot_common-msg:y instead.")
  (y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Point2d>) ostream)
  "Serializes a message object of type '<Point2d>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Point2d>) istream)
  "Deserializes a message object of type '<Point2d>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Point2d>)))
  "Returns string type for a message object of type '<Point2d>"
  "nubot_common/Point2d")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Point2d)))
  "Returns string type for a message object of type 'Point2d"
  "nubot_common/Point2d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Point2d>)))
  "Returns md5sum for a message object of type '<Point2d>"
  "ff8d7d66dd3e4b731ef14a45d38888b6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Point2d)))
  "Returns md5sum for a message object of type 'Point2d"
  "ff8d7d66dd3e4b731ef14a45d38888b6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Point2d>)))
  "Returns full string definition for message of type '<Point2d>"
  (cl:format cl:nil "float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Point2d)))
  "Returns full string definition for message of type 'Point2d"
  (cl:format cl:nil "float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Point2d>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Point2d>))
  "Converts a ROS message object to a list"
  (cl:list 'Point2d
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
))
