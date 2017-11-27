;; Auto-generated. Do not edit!


(when (boundp 'allocation::DebugInfo)
  (if (not (find-package "ALLOCATION"))
    (make-package "ALLOCATION"))
  (shadow 'DebugInfo (find-package "ALLOCATION")))
(unless (find-package "ALLOCATION::DEBUGINFO")
  (make-package "ALLOCATION::DEBUGINFO"))

(in-package "ROS")
;;//! \htmlinclude DebugInfo.msg.html


(defclass allocation::DebugInfo
  :super ros::object
  :slots (_d1 _d2 ))

(defmethod allocation::DebugInfo
  (:init
   (&key
    ((:d1 __d1) 0.0)
    ((:d2 __d2) 0.0)
    )
   (send-super :init)
   (setq _d1 (float __d1))
   (setq _d2 (float __d2))
   self)
  (:d1
   (&optional __d1)
   (if __d1 (setq _d1 __d1)) _d1)
  (:d2
   (&optional __d2)
   (if __d2 (setq _d2 __d2)) _d2)
  (:serialization-length
   ()
   (+
    ;; float32 _d1
    4
    ;; float32 _d2
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _d1
       (sys::poke _d1 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _d2
       (sys::poke _d2 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _d1
     (setq _d1 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _d2
     (setq _d2 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get allocation::DebugInfo :md5sum-) "1c78ad82c247783d0c3aa95ce147b845")
(setf (get allocation::DebugInfo :datatype-) "allocation/DebugInfo")
(setf (get allocation::DebugInfo :definition-)
      "float32 d1
float32 d2

")



(provide :allocation/DebugInfo "1c78ad82c247783d0c3aa95ce147b845")


