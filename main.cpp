#include <iostream>
#include <fstream>
#include <Python.h>
#include <arrayobject.h>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <list>

using namespace std;
using namespace cv;

#pragma region ����ɸѡ�ӿڣ���һ������Ϊ��������򣬵ڶ�������Ϊɸѡǰ��ȫ����,���ķֱ�ΪͼƬ�Ŀ��

struct box
{
	double x1;
	double y1;
	double x2;
	double y2;
};


vector<box> DectectionFilter(vector<cv::Point2f> contour, vector<box> all_boxes, int w, int h)
{
	cout << "ɸѡ��" << endl;
	for (int i = 0;i < all_boxes.size();i++)
	{
		cout << "x1" << all_boxes[i].x1 << "y1" << all_boxes[i].y1 << "x2" << all_boxes[i].x2 << "y2" << all_boxes[i].y2 << endl;
	}
	//дһ�㱣��
	if (contour.empty())
	{
		cout << "δ����ɸѡ���򣡣�";
		return all_boxes;
	}
	if (all_boxes.empty())
	{
		cout << "û��ɸѡ�򣡣�";
		return all_boxes;
	}

	//���������Ŀ���Ϣ
	vector<box> boxes;
	//��ʱ����
	float tempX, tempY;
	//���������Ϊ���ֵ����Ҫת��Ϊ����ֵ
	for (int i = 0; i < contour.size(); i++)
	{
		contour[i].x = contour[i].x * w;
		contour[i].y = contour[i].y * h;
	}
	//��ʼɸѡ
	for (int i = 0; i < all_boxes.size(); i++)
	{
		//������Ŀ���Ե����ĵ�
		tempX = all_boxes[i].x1+(all_boxes[i].x2 - all_boxes[i].x1) / 2;
		tempY = all_boxes[i].y2+(all_boxes[i].y1 - all_boxes[i].y2) / 2;
		//�жϸõ��Ƿ��������ڣ����һ������Ϊtureʱ����ʵ�ʵľ���
		Point2f point;
		point.x = tempX;
		point.y = tempY;

		if (pointPolygonTest(contour, point, false) == 1)
		{
			box tempbox = { all_boxes[i].x1,all_boxes[i].y1,all_boxes[i].x2,all_boxes[i].y2 };
			boxes.push_back(tempbox);
		}
	}
	return boxes;
}
#pragma endregion




int main()
{
	
	Py_SetPythonHome(L"D:/sdk/python3");
	Py_Initialize();


	// ����ǰĿ¼����sys.path
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");

	// Create some Python objects that will later be assigned values.
	PyObject* pModule, * pDict, * pFunc_add, * pFunc_hello, * pArgs, * pValue;

	// Import the file as a Python module.
	pModule = PyImport_ImportModule("interface");
	if (!pModule)
		std::cout << "Module Import Error" << std::endl;
	// Create a dictionary for the contents of the module.
	//pDict = PyModule_GetDict(pModule);
	PyObject* pClassInterface = PyObject_GetAttrString(pModule, "Interface");
	// Create a Python tuple to hold the arguments to the method.
	PyObject* pArgInterface = PyTuple_New(0);
	//ʵ����һ���࣬����û�в������룬��Ҫ��һ����TupleArray
	PyObject* pInstanceInterface = PyObject_Call(pClassInterface, pArgInterface, NULL);

	PyObject* ArgList = PyTuple_New(1);

	cv::Mat img = cv::imread("./road.jpeg", cv::IMREAD_COLOR);
	auto sz = img.size();
	int x = sz.width;
	int y = sz.height;
	int z = img.channels();
	uchar* CArrays = new uchar[x * y * z];
	int iChannels = img.channels();
	int iRows = img.rows;
	int iCols = img.cols * iChannels;
	if (img.isContinuous())
	{
		iCols *= iRows;
		iRows = 1;
	}

	uchar* p;
	int id = -1;
	for (int i = 0; i < iRows; i++)
	{
		// get the pointer to the ith row
		p = img.ptr<uchar>(i);
		// operates on each pixel
		for (int j = 0; j < iCols; j++)
		{
			CArrays[++id] = p[j];//�����ռ�
		}
	}

	import_array();//���Ҫ����ͼƬ������python �ű�����ؼ��ϸþ䣬��numpy����

	npy_intp Dims[3] = { y, x, z }; //ע�����ά�����ݣ�
	PyObject* PyArray = PyArray_SimpleNewFromData(3, Dims, NPY_UBYTE, CArrays);
	PyObject* ArgArray = PyTuple_New(1);
	PyTuple_SetItem(ArgArray, 0, PyArray);
	PyObject* pResult = PyObject_CallMethod(pInstanceInterface, "detect", "O", ArgArray);

	//Print a message if calling the method failed.
	if (pResult == NULL)
		printf("Calling the add method failed.\n");

	int LongList = PyList_Size(pResult);
	cout << "LongList:" << LongList << endl;

	vector<box> all_boxes;
	for (int i = 0;i < LongList;i++)
	{
		PyObject* ListItem = PyList_GetItem(pResult, i);

		double x1 = PyFloat_AsDouble(PyList_GetItem(ListItem, 0));
		double y1 = PyFloat_AsDouble(PyList_GetItem(ListItem, 1));
		double x2 = PyFloat_AsDouble(PyList_GetItem(ListItem, 2));
		double y2 = PyFloat_AsDouble(PyList_GetItem(ListItem, 3));
		double pro = PyFloat_AsDouble(PyList_GetItem(ListItem, 4));
		int cls = _PyLong_AsInt(PyList_GetItem(ListItem, 5));

		cout << "C++ print info" << i << endl;
		cout << x1 << endl;
		cout << y1 << endl;
		cout << x2 << endl;
		cout << y2 << endl;
		cout << pro << endl;
		cout << cls << endl;
		box tmp = { x1,y1,x2,y2 };
		all_boxes.push_back(tmp);
	}
	// Destroy the Python interpreter.
	Py_Finalize();
	// Print the result.
	printf("Calling Python Finalized.\n");

	imshow("lala", img);
	cin.get();
	return 0;

	vector<cv::Point2f> contour = { Point2f(0.45,0.38),Point2f(0.67,0.14),Point2f(0.89,0.37),Point2f(0.81,0.78),Point2f(0.55,0.78) };
	vector<box> boxes = DectectionFilter(contour, all_boxes, 750, 468);
	

	
	for (int i = 0;i < boxes.size();i++)
	{
		// cvRectangle���������� ͼƬ�� ���Ͻǣ� ���½ǣ� ��ɫ�� ������ϸ�� �������ͣ�������  
		rectangle(img, Point2f(boxes[i].x1, boxes[i].y1), Point2f(boxes[i].x2, boxes[i].y2), Scalar(0, 0, 255), 3, 4, 0);

		cout << "x1 " << boxes[i].x1 << "  y1 "<< boxes[i].y1<< "  x2 " << boxes[i].x2 << "  y2 " << boxes[i].y2 <<endl;
	}
	namedWindow("lala");
	imshow("lala", img);
	waitKey();
	//����ͼƬ
	//imwrite("./name.jpg", img);
	cout << "end" << endl;
}
