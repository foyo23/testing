
/* Data [execute_cases] */
insert into [execute_cases] values(1, '更换设备', '', '2012-07-26 09:57:08.000', '2012-07-26 09:57:08.000');
insert into [execute_cases] values(2, '注意设备', '', '2012-07-26 09:57:08.000', '2012-07-26 09:57:08.000');
insert into [execute_cases] values(3, '查看设备', '', '2012-07-26 09:57:08.000', '2012-07-26 09:57:08.000');


/* Table structure [fault_degrees] */


/* Data [fault_natures] */
insert into [fault_natures] values(1, '正常', '', '2012-07-26 09:57:08.000', '2012-10-24 09:45:15.000');
insert into [fault_natures] values(2, '关注', '', '2012-07-26 09:57:08.000', '2012-07-26 09:57:08.000');
insert into [fault_natures] values(3, '一般缺陷', '', '2012-07-26 09:57:08.000', '2012-07-26 09:57:08.000');
insert into [fault_natures] values(4, '严重缺陷', '', '2012-07-26 09:57:08.000', '2012-07-26 09:57:08.000');
insert into [fault_natures] values(5, '危急缺陷', '', '2012-07-26 09:57:08.000', '2012-07-26 09:57:08.000');
insert into [fault_natures] values(100, '未知', '', '2012-07-26 09:57:08.000', '2012-07-26 09:57:08.000');


/* Table structure [fix_methods] */

/* Data [fix_methods] */
insert into [fix_methods] values(1, '消缺一', '', '2012-07-26 09:57:08.000', '2012-07-26 09:57:08.000');
insert into [fix_methods] values(2, '严重消缺', '', '2012-07-26 09:57:08.000', '2012-07-26 09:57:08.000');
insert into [fix_methods] values(3, '正常消缺', '', '2012-07-26 09:57:08.000', '2012-07-26 09:57:08.000');



/* Enable Foreign Keys */
pragma foreign_keys = on;
