;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::Shoot)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'Shoot (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::SHOOT")
  (make-package "NUBOT_COMMON::SHOOT"))
(unless (find-package "NUBOT_COMMON::SHOOTREQUEST")
  (make-package "NUBOT_COMMON::SHOOTREQUEST"))
(unless (find-package "NUBOT_COMMON::SHOOTRESPONSE")
  (make-package "NUBOT_COMMON::SHOOTRESPONSE"))

(in-package "ROS")





(defclass nubot_common::ShootRequest
  :super ros::object
  :slots (_strength _ShootPos ))

(defmethod nubot_common::ShootRequest
  (:init
   (&key
    ((:strength __strength) 0.0)
    ((:ShootPos __ShootPos) 0)
    )
   (send-super :init)
   (setq _strength (float __strength))
   (setq _ShootPos (round __ShootPos))
   self)
  (:strength
   (&optional __strength)
   (if __strength (setq _strength __strength)) _strength)
  (:ShootPos
   (&optional __ShootPos)
   (if __ShootPos (setq _ShootPos __ShootPos)) _ShootPos)
  (:serialization-length
   ()
   (+
    ;; float32 _strength
    4
    ;; int64 _ShootPos
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _strength
       (sys::poke _strength (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int64 _ShootPos
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _ShootPos (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _ShootPos) (= (length (_ShootPos . bv)) 2)) ;; bignum
              (write-long (ash (elt (_ShootPos . bv) 0) 0) s)
              (write-long (ash (elt (_ShootPos . bv) 1) -1) s))
             ((and (class _ShootPos) (= (length (_ShootPos . bv)) 1)) ;; big1
              (write-long (elt (_ShootPos . bv) 0) s)
              (write-long (if (>= _ShootPos 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _ShootPos s)(write-long (if (>= _ShootPos 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _strength
     (setq _strength (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int64 _ShootPos
#+(or :alpha :irix6 :x86_64)
      (setf _ShootPos (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _ShootPos (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(defclass nubot_common::ShootResponse
  :super ros::object
  :slots (_ShootIsDone ))

(defmethod nubot_common::ShootResponse
  (:init
   (&key
    ((:ShootIsDone __ShootIsDone) 0)
    )
   (send-super :init)
   (setq _ShootIsDone (round __ShootIsDone))
   self)
  (:ShootIsDone
   (&optional __ShootIsDone)
   (if __ShootIsDone (setq _ShootIsDone __ShootIsDone)) _ShootIsDone)
  (:serialization-length
   ()
   (+
    ;; int64 _ShootIsDone
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _ShootIsDone
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _ShootIsDone (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _ShootIsDone) (= (length (_ShootIsDone . bv)) 2)) ;; bignum
              (write-long (ash (elt (_ShootIsDone . bv) 0) 0) s)
              (write-long (ash (elt (_ShootIsDone . bv) 1) -1) s))
             ((and (class _ShootIsDone) (= (length (_ShootIsDone . bv)) 1)) ;; big1
              (write-long (elt (_ShootIsDone . bv) 0) s)
              (write-long (if (>= _ShootIsDone 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _ShootIsDone s)(write-long (if (>= _ShootIsDone 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _ShootIsDone
#+(or :alpha :irix6 :x86_64)
      (setf _ShootIsDone (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _ShootIsDone (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(defclass nubot_common::Shoot
  :super ros::object
  :slots ())

(setf (get nubot_common::Shoot :md5sum-) "5f7b2fca861afe65dc92d3f6a153bbec")
(setf (get nubot_common::Shoot :datatype-) "nubot_common/Shoot")
(setf (get nubot_common::Shoot :request) nubot_common::ShootRequest)
(setf (get nubot_common::Shoot :response) nubot_common::ShootResponse)

(defmethod nubot_common::ShootRequest
  (:response () (instance nubot_common::ShootResponse :init)))

(setf (get nubot_common::ShootRequest :md5sum-) "5f7b2fca861afe65dc92d3f6a153bbec")
(setf (get nubot_common::ShootRequest :datatype-) "nubot_common/ShootRequest")
(setf (get nubot_common::ShootRequest :definition-)
      "float32 strength
int64 ShootPos
---
int64 ShootIsDone

")

(setf (get nubot_common::ShootResponse :md5sum-) "5f7b2fca861afe65dc92d3f6a153bbec")
(setf (get nubot_common::ShootResponse :datatype-) "nubot_common/ShootResponse")
(setf (get nubot_common::ShootResponse :definition-)
      "float32 strength
int64 ShootPos
---
int64 ShootIsDone

")



(provide :nubot_common/Shoot "5f7b2fca861afe65dc92d3f6a153bbec")


