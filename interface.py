# import cv2
# import numpy as np
# import utils as utils
# import tensorflow as tf
# import queue
# from PIL import Image
import logging.handlers, os

#---------------------------------log ------------------------------------------------
log_level = logging.DEBUG
#rq = time.strftime('%Y%m%d%H%M', time.localtime(time.time()))
#log_path = os.path.dirname(os.getcwd()) + '/Logs/'
#log_name = log_path + rq + '.log'
logger = logging.getLogger("interface.py")
log_fmt = logging.Formatter("%(asctime)s - %(levelname)s - %(filename)s(%(lineno)d) - %(funcName)s: %(message)s")
logger.setLevel(log_level)

if not os.path.exists("logs"):
    os.mkdir("logs")
log_file = "logs/{0}_{1}.log".format(__name__, os.getpid())
log_handler = logging.handlers.TimedRotatingFileHandler(log_file, when="D", interval=1,
                                                        backupCount=7)
log_handler.setFormatter(log_fmt)
logger.addHandler(log_handler)

console_handler = logging.StreamHandler()
console_handler.setLevel(log_level)
console_handler.setFormatter(log_fmt)
logger.addHandler(console_handler)
#---------------------------------log end ---------------------------------------------
# 所有py文件下相对路径均为main.cpp相对路径
class Interface:

    def __init__(self):
        logger.info("interface init")
        print("init")
        # # network params
        # self.return_elements = ["input/input_data:0", "pred_sbbox/concat_2:0", "pred_mbbox/concat_2:0",
        #                         "pred_lbbox/concat_2:0"]
        # self.pb_file = "./yolov3_coco.pb"
        # self.image_path = "./road.jpeg"
        # self.num_classes = 80
        # self.input_size = 416
        # self.graph = tf.Graph()
        # # self.original_image = cv2.imread(self.image_path)
        # # self.original_image = cv2.cvtColor(self.original_image, cv2.COLOR_BGR2RGB)
        # # self.original_image_size = self.original_image.shape[:2]
        # # self.image_data = utils.image_preporcess(np.copy(self.original_image), [self.input_size, self.input_size])
        # # self.image_data = self.image_data[np.newaxis, ...]
        # self.return_tensors = utils.read_pb_return_tensors(self.graph, self.pb_file, self.return_elements)
        # self.sess = tf.Session(graph=self.graph)
        # # interface params
        print("init end")

    def detect(self, original_image):
        logger.info("call detect")
        print("detect")
        # # cv2.imshow("img", img_array)
        # # cv2.waitKey(0)
        #
        # original_image = cv2.cvtColor(original_image, cv2.COLOR_BGR2RGB)
        # original_image_size = original_image.shape[:2]
        # print("detect 1")
        #
        # image_data = utils.image_preporcess(np.copy(original_image), [self.input_size, self.input_size])
        # print("detect 2")
        #
        # image_data = image_data[np.newaxis, ...]
        # print("detect 3")
        #
        # # self.original_image = cv2.cvtColor(self.original_image, cv2.COLOR_BGR2RGB)
        # # self.original_image_size = self.original_image.shape[:2]
        # # self.image_data = utils.image_preporcess(np.copy(self.original_image), [self.input_size, self.input_size])
        # # self.image_data = self.image_data[np.newaxis, ...]
        #
        # print(self.sess)
        # pred_sbbox, pred_mbbox, pred_lbbox = self.sess.run(
        #     [self.return_tensors[1], self.return_tensors[2], self.return_tensors[3]],
        #     feed_dict={self.return_tensors[0]: image_data})
        # pred_bbox = np.concatenate([np.reshape(pred_sbbox, (-1, 5 + self.num_classes)),
        #                             np.reshape(pred_mbbox, (-1, 5 + self.num_classes)),
        #                             np.reshape(pred_lbbox, (-1, 5 + self.num_classes))], axis=0)
        # bboxes = utils.postprocess_boxes(pred_bbox, original_image_size, self.input_size, 0.3)
        # bboxes = utils.nms(bboxes, 0.45, method='nms')
        # image = utils.draw_bbox(original_image, bboxes)
        # image = Image.fromarray(image)
        # image.show()
        print("detect finished")
        # for i in range(len(bboxes)):
        #     result.append(bboxes[i].tolist())
        result = [[225.52558899, 35.52573776, 379.40240479, 416.01052856, 0.99694991, 15.],
                  [366.99118042, 74.88848877, 506.62991333, 374.6340332, 0.99644434, 15.],
                  [57.64980698, 39.82318497, 241.01026917, 422.93823242, 0.99474263, 15.],
                  [491.75143433, 72.5313797, 691.62438965, 380.12191772, 0.98958373, 15.],
                  ]

        print(result)
        return result
        # [检测的类别[左上x1,左上y1,右下x2，右下y2,置信度，类别]]
        # [array([225.52558899,  35.52573776, 379.40240479, 416.01052856,0.99694991,  15.        ]),
        #  array([366.99118042,  74.88848877, 506.62991333, 374.6340332 ,0.99644434,  15.        ]),
        #  array([57.64980698,  39.82318497, 241.01026917, 422.93823242, 0.99474263,  15.        ]),
        #  array([491.75143433,  72.5313797 , 691.62438965, 380.12191772,0.98958373,  15.        ])]
