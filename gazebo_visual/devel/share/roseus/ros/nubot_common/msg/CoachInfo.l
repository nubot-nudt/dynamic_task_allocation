;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::CoachInfo)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'CoachInfo (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::COACHINFO")
  (make-package "NUBOT_COMMON::COACHINFO"))

(in-package "ROS")
;;//! \htmlinclude CoachInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nubot_common::CoachInfo
  :super ros::object
  :slots (_header _MatchMode _MatchType _TestMode _pointA _pointB _angleA _angleB _idA _idB _kickforce ))

(defmethod nubot_common::CoachInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:MatchMode __MatchMode) 0)
    ((:MatchType __MatchType) 0)
    ((:TestMode __TestMode) 0)
    ((:pointA __pointA) (instance nubot_common::Point2d :init))
    ((:pointB __pointB) (instance nubot_common::Point2d :init))
    ((:angleA __angleA) 0)
    ((:angleB __angleB) 0)
    ((:idA __idA) 0)
    ((:idB __idB) 0)
    ((:kickforce __kickforce) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _MatchMode (round __MatchMode))
   (setq _MatchType (round __MatchType))
   (setq _TestMode (round __TestMode))
   (setq _pointA __pointA)
   (setq _pointB __pointB)
   (setq _angleA (round __angleA))
   (setq _angleB (round __angleB))
   (setq _idA (round __idA))
   (setq _idB (round __idB))
   (setq _kickforce (round __kickforce))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:MatchMode
   (&optional __MatchMode)
   (if __MatchMode (setq _MatchMode __MatchMode)) _MatchMode)
  (:MatchType
   (&optional __MatchType)
   (if __MatchType (setq _MatchType __MatchType)) _MatchType)
  (:TestMode
   (&optional __TestMode)
   (if __TestMode (setq _TestMode __TestMode)) _TestMode)
  (:pointA
   (&rest __pointA)
   (if (keywordp (car __pointA))
       (send* _pointA __pointA)
     (progn
       (if __pointA (setq _pointA (car __pointA)))
       _pointA)))
  (:pointB
   (&rest __pointB)
   (if (keywordp (car __pointB))
       (send* _pointB __pointB)
     (progn
       (if __pointB (setq _pointB (car __pointB)))
       _pointB)))
  (:angleA
   (&optional __angleA)
   (if __angleA (setq _angleA __angleA)) _angleA)
  (:angleB
   (&optional __angleB)
   (if __angleB (setq _angleB __angleB)) _angleB)
  (:idA
   (&optional __idA)
   (if __idA (setq _idA __idA)) _idA)
  (:idB
   (&optional __idB)
   (if __idB (setq _idB __idB)) _idB)
  (:kickforce
   (&optional __kickforce)
   (if __kickforce (setq _kickforce __kickforce)) _kickforce)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; char _MatchMode
    1
    ;; char _MatchType
    1
    ;; char _TestMode
    1
    ;; nubot_common/Point2d _pointA
    (send _pointA :serialization-length)
    ;; nubot_common/Point2d _pointB
    (send _pointB :serialization-length)
    ;; int16 _angleA
    2
    ;; int16 _angleB
    2
    ;; char _idA
    1
    ;; char _idB
    1
    ;; char _kickforce
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; char _MatchMode
       (write-byte _MatchMode s)
     ;; char _MatchType
       (write-byte _MatchType s)
     ;; char _TestMode
       (write-byte _TestMode s)
     ;; nubot_common/Point2d _pointA
       (send _pointA :serialize s)
     ;; nubot_common/Point2d _pointB
       (send _pointB :serialize s)
     ;; int16 _angleA
       (write-word _angleA s)
     ;; int16 _angleB
       (write-word _angleB s)
     ;; char _idA
       (write-byte _idA s)
     ;; char _idB
       (write-byte _idB s)
     ;; char _kickforce
       (write-byte _kickforce s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; char _MatchMode
     (setq _MatchMode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _MatchType
     (setq _MatchType (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _TestMode
     (setq _TestMode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; nubot_common/Point2d _pointA
     (send _pointA :deserialize buf ptr-) (incf ptr- (send _pointA :serialization-length))
   ;; nubot_common/Point2d _pointB
     (send _pointB :deserialize buf ptr-) (incf ptr- (send _pointB :serialization-length))
   ;; int16 _angleA
     (setq _angleA (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _angleB
     (setq _angleB (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; char _idA
     (setq _idA (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _idB
     (setq _idB (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _kickforce
     (setq _kickforce (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get nubot_common::CoachInfo :md5sum-) "7bb01a0f4328cb28beb61d4f502c2969")
(setf (get nubot_common::CoachInfo :datatype-) "nubot_common/CoachInfo")
(setf (get nubot_common::CoachInfo :definition-)
      "Header header
char MatchMode
char MatchType
char TestMode           
Point2d pointA
Point2d pointB
int16 angleA
int16 angleB
char idA
char idB
char kickforce

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: nubot_common/Point2d
float32 x
float32 y

")



(provide :nubot_common/CoachInfo "7bb01a0f4328cb28beb61d4f502c2969")


