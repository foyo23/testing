-- MySQL dump 10.13  Distrib 5.5.29, for Linux (x86_64)
--
-- Host: localhost    Database: yfplatform_production
-- ------------------------------------------------------
-- Server version	5.5.29

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `detect_rules`
--

DROP TABLE IF EXISTS `detect_rules`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `detect_rules` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `outline_id` int(11) NOT NULL,
  `fault_nature_id` int(11) NOT NULL,
  `order_num` int(11) NOT NULL,
  `rule_title` varchar(255) NOT NULL DEFAULT '',
  `rule_text` text,
  `rule_formula` text,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`outline_id`,`fault_nature_id`,`order_num`),
  KEY `index_detect_rules_on_outline_id` (`outline_id`),
  KEY `index_detect_rules_on_fault_nature_id` (`fault_nature_id`)
) ENGINE=InnoDB AUTO_INCREMENT=1485 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `detection_resources`
--

DROP TABLE IF EXISTS `detection_resources`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `detection_resources` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `detection_id` int(11) NOT NULL,
  `irv_pos_start` int(11) DEFAULT NULL,
  `irv_pos_end` int(11) DEFAULT NULL,
  `key_frames` varchar(255) DEFAULT NULL,
  `params_json` text,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  `irp_file_name` varchar(255) DEFAULT NULL,
  `irp_content_type` varchar(255) DEFAULT NULL,
  `irp_file_size` int(11) DEFAULT NULL,
  `irp_updated_at` datetime DEFAULT NULL,
  `irjson_file_name` varchar(255) DEFAULT NULL,
  `irjson_content_type` varchar(255) DEFAULT NULL,
  `irjson_file_size` int(11) DEFAULT NULL,
  `irjson_updated_at` datetime DEFAULT NULL,
  `irimage_file_name` varchar(255) DEFAULT NULL,
  `irimage_content_type` varchar(255) DEFAULT NULL,
  `irimage_file_size` int(11) DEFAULT NULL,
  `irimage_updated_at` datetime DEFAULT NULL,
  `viimage_file_name` varchar(255) DEFAULT NULL,
  `viimage_content_type` varchar(255) DEFAULT NULL,
  `viimage_file_size` int(11) DEFAULT NULL,
  `viimage_updated_at` datetime DEFAULT NULL,
  `irv_file_name` varchar(255) DEFAULT NULL,
  `irv_content_type` varchar(255) DEFAULT NULL,
  `irv_file_size` int(11) DEFAULT NULL,
  `irv_updated_at` datetime DEFAULT NULL,
  `irp_md5` varchar(32) DEFAULT NULL,
  `irjson_md5` varchar(32) DEFAULT NULL,
  `irimage_md5` varchar(32) DEFAULT NULL,
  `viimage_md5` varchar(32) DEFAULT NULL,
  `irv_md5` varchar(32) DEFAULT NULL,
  `ana_unit_text` text,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_detection_resources_on_detection_id` (`detection_id`),
  KEY `irimage_file_name` (`irimage_file_name`)
) ENGINE=InnoDB AUTO_INCREMENT=192304 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `detections`
--

DROP TABLE IF EXISTS `detections`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `detections` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `detect_date` date NOT NULL,
  `detect_time` time NOT NULL,
  `device_id` int(11) NOT NULL,
  `part_position_id` int(11) NOT NULL,
  `fault_nature_id` int(11) DEFAULT NULL,
  `fixed_date` datetime DEFAULT NULL,
  `fix_method_id` int(11) DEFAULT NULL,
  `execute_case_id` int(11) DEFAULT NULL,
  `fault_degree_id` int(11) DEFAULT NULL,
  `detect_rule_id` int(11) DEFAULT NULL,
  `running_voltage` float DEFAULT NULL,
  `electrical_current` float DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  `substation_id` int(11) NOT NULL,
  `device_area_id` int(11) NOT NULL,
  `device_area_voltage_id` int(11) NOT NULL,
  `device_type_id` int(11) NOT NULL,
  `model_style_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`device_id`,`part_position_id`,`detect_date`,`detect_time`),
  KEY `idx_substation_id` (`substation_id`),
  KEY `idx_substation_id_and_detect_datetime` (`detect_date`,`detect_time`,`substation_id`),
  KEY `detect_datetime` (`detect_date`,`detect_time`)
) ENGINE=InnoDB AUTO_INCREMENT=192282 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `device_area_shoot_sequences`
--

DROP TABLE IF EXISTS `device_area_shoot_sequences`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `device_area_shoot_sequences` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `shoot_sequence_id` int(11) NOT NULL,
  `order_num` int(11) NOT NULL,
  `device_area_id` int(11) NOT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`shoot_sequence_id`,`device_area_id`),
  KEY `index_device_area_shoot_sequences_on_shoot_sequence_id` (`shoot_sequence_id`),
  KEY `index_device_area_shoot_sequences_on_device_area_id` (`device_area_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4799 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `device_area_types`
--

DROP TABLE IF EXISTS `device_area_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `device_area_types` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `notes` varchar(255) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_device_area_types_on_name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `device_areas`
--

DROP TABLE IF EXISTS `device_areas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `device_areas` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `substation_id` int(11) NOT NULL DEFAULT '0',
  `voltage_level_id` int(11) NOT NULL DEFAULT '0',
  `device_area_name` varchar(255) NOT NULL DEFAULT '',
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  `longitude` float DEFAULT NULL,
  `latitude` float DEFAULT NULL,
  `altitude` float DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`substation_id`,`voltage_level_id`,`device_area_name`),
  KEY `index_device_areas_on_substation_id` (`substation_id`),
  KEY `index_device_areas_on_device_area_name` (`device_area_name`),
  KEY `index_device_areas_on_voltage_level_id` (`voltage_level_id`)
) ENGINE=InnoDB AUTO_INCREMENT=35376 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `device_shoot_sequences`
--

DROP TABLE IF EXISTS `device_shoot_sequences`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `device_shoot_sequences` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `shoot_sequence_id` int(11) NOT NULL,
  `device_area_id` int(11) NOT NULL,
  `order_num` int(11) NOT NULL,
  `device_id` int(11) NOT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`shoot_sequence_id`,`device_area_id`,`order_num`),
  KEY `index_device_shoot_sequences_on_shoot_sequence_id` (`shoot_sequence_id`),
  KEY `index_device_shoot_sequences_on_device_area_id` (`device_area_id`),
  KEY `index_device_shoot_sequences_on_device_id` (`device_id`)
) ENGINE=InnoDB AUTO_INCREMENT=50961 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `device_types`
--

DROP TABLE IF EXISTS `device_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `device_types` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `notes` varchar(255) DEFAULT NULL,
  `parent_id` int(11) NOT NULL DEFAULT '0',
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`parent_id`,`name`),
  KEY `index_device_types_on_name` (`name`),
  KEY `index_device_types_on_parent_id` (`parent_id`)
) ENGINE=InnoDB AUTO_INCREMENT=228 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `devices`
--

DROP TABLE IF EXISTS `devices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `devices` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `device_area_id` int(11) NOT NULL DEFAULT '0',
  `model_style_id` int(11) NOT NULL DEFAULT '0',
  `device_type_id` int(11) DEFAULT NULL,
  `substation_id` int(11) DEFAULT NULL,
  `voltage_level_id` int(11) DEFAULT NULL,
  `phasic` varchar(255) NOT NULL DEFAULT '',
  `local_scene_name` varchar(255) DEFAULT NULL,
  `vender_id` int(11) DEFAULT '0',
  `cur_status` int(11) DEFAULT '1',
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`device_area_id`,`model_style_id`,`phasic`,`local_scene_name`),
  KEY `index_devices_on_device_area_id` (`device_area_id`),
  KEY `index_devices_on_model_style_id` (`model_style_id`),
  KEY `index_devices_on_substation_id` (`substation_id`)
) ENGINE=InnoDB AUTO_INCREMENT=193852 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `employees`
--

DROP TABLE IF EXISTS `employees`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `employees` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(255) NOT NULL DEFAULT '',
  `name` varchar(255) NOT NULL DEFAULT '',
  `mobile` varchar(255) DEFAULT NULL,
  `tel` varchar(255) DEFAULT NULL,
  `region_id` int(11) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_employees_on_email` (`email`),
  KEY `index_employees_on_name` (`name`),
  KEY `index_employees_on_region_id` (`region_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `execute_cases`
--

DROP TABLE IF EXISTS `execute_cases`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `execute_cases` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `notes` varchar(255) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_execute_cases_on_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `fault_degrees`
--

DROP TABLE IF EXISTS `fault_degrees`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `fault_degrees` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `notes` varchar(255) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_fault_degrees_on_name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `fault_natures`
--

DROP TABLE IF EXISTS `fault_natures`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `fault_natures` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `notes` varchar(255) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_fault_natures_on_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=101 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `fix_methods`
--

DROP TABLE IF EXISTS `fix_methods`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `fix_methods` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `notes` varchar(255) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_fix_methods_on_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `group_permissions`
--

DROP TABLE IF EXISTS `group_permissions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `group_permissions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `group_id` int(11) NOT NULL,
  `substation_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `index_group_permissions_on_group_id` (`group_id`),
  KEY `index_group_permissions_on_substation_id` (`substation_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `model_styles`
--

DROP TABLE IF EXISTS `model_styles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `model_styles` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `model_style` varchar(255) NOT NULL DEFAULT '',
  `name` varchar(255) DEFAULT NULL,
  `notes` varchar(255) DEFAULT NULL,
  `device_type_id` int(11) NOT NULL,
  `voltage_level_id` int(11) NOT NULL DEFAULT '0',
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`device_type_id`,`voltage_level_id`,`model_style`)
) ENGINE=InnoDB AUTO_INCREMENT=98251 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `oauth_access_grants`
--

DROP TABLE IF EXISTS `oauth_access_grants`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `oauth_access_grants` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `resource_owner_id` int(11) NOT NULL,
  `application_id` int(11) NOT NULL,
  `token` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `expires_in` int(11) NOT NULL,
  `redirect_uri` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `created_at` datetime NOT NULL,
  `revoked_at` datetime DEFAULT NULL,
  `scopes` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_oauth_access_grants_on_token` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `oauth_access_tokens`
--

DROP TABLE IF EXISTS `oauth_access_tokens`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `oauth_access_tokens` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `resource_owner_id` int(11) DEFAULT NULL,
  `application_id` int(11) NOT NULL,
  `token` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `refresh_token` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `expires_in` int(11) DEFAULT NULL,
  `revoked_at` datetime DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `scopes` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_oauth_access_tokens_on_token` (`token`),
  UNIQUE KEY `index_oauth_access_tokens_on_refresh_token` (`refresh_token`),
  KEY `index_oauth_access_tokens_on_resource_owner_id` (`resource_owner_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `oauth_applications`
--

DROP TABLE IF EXISTS `oauth_applications`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `oauth_applications` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `uid` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `secret` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `redirect_uri` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `owner_id` int(11) DEFAULT NULL,
  `owner_type` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_oauth_applications_on_uid` (`uid`),
  KEY `index_oauth_applications_on_owner_id_and_owner_type` (`owner_id`,`owner_type`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `outlines`
--

DROP TABLE IF EXISTS `outlines`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `outlines` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `model_style_id` int(11) NOT NULL,
  `part_position_id` int(11) NOT NULL,
  `outline_text` text,
  `ana_unit_text` text,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  `outline_vector_file_name` varchar(255) DEFAULT NULL,
  `outline_vector_content_type` varchar(255) DEFAULT NULL,
  `outline_vector_file_size` int(11) DEFAULT NULL,
  `outline_vector_updated_at` datetime DEFAULT NULL,
  `standard_ir_file_name` varchar(255) DEFAULT NULL,
  `standard_ir_content_type` varchar(255) DEFAULT NULL,
  `standard_ir_file_size` int(11) DEFAULT NULL,
  `standard_ir_updated_at` datetime DEFAULT NULL,
  `standard_vi_file_name` varchar(255) DEFAULT NULL,
  `standard_vi_content_type` varchar(255) DEFAULT NULL,
  `standard_vi_file_size` int(11) DEFAULT NULL,
  `standard_vi_updated_at` datetime DEFAULT NULL,
  `rule_unsatisfy` tinyint(1) DEFAULT '0',
  `outline_vector_md5` varchar(32) DEFAULT NULL,
  `standard_ir_md5` varchar(32) DEFAULT NULL,
  `standard_vi_md5` varchar(32) DEFAULT NULL,
  `outline_vector_unsatisfy` tinyint(1) DEFAULT '0',
  `standard_ir_unsatisfy` tinyint(1) DEFAULT '0',
  `standard_vi_unsatisfy` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`model_style_id`,`part_position_id`),
  KEY `index_outlines_on_model_style_id` (`model_style_id`),
  KEY `index_outlines_on_part_position_id` (`part_position_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4445 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `part_position_shoot_sequences`
--

DROP TABLE IF EXISTS `part_position_shoot_sequences`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `part_position_shoot_sequences` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `shoot_sequence_id` int(11) NOT NULL,
  `device_area_id` int(11) NOT NULL,
  `device_id` int(11) NOT NULL,
  `order_num` int(11) NOT NULL,
  `part_position_id` int(11) NOT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`shoot_sequence_id`,`device_area_id`,`device_id`,`order_num`),
  KEY `index_part_position_shoot_sequences_on_shoot_sequence_id` (`shoot_sequence_id`),
  KEY `index_part_position_shoot_sequences_on_device_area_id` (`device_area_id`),
  KEY `index_part_position_shoot_sequences_on_device_id` (`device_id`),
  KEY `index_part_position_shoot_sequences_on_part_position_id` (`part_position_id`)
) ENGINE=InnoDB AUTO_INCREMENT=51004 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `part_positions`
--

DROP TABLE IF EXISTS `part_positions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `part_positions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `notes` varchar(255) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_part_positions_on_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `permissions`
--

DROP TABLE IF EXISTS `permissions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `permissions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `substation_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `index_permissions_on_user_id` (`user_id`),
  KEY `index_permissions_on_substation_id` (`substation_id`)
) ENGINE=InnoDB AUTO_INCREMENT=50510 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `region_device_areas`
--

DROP TABLE IF EXISTS `region_device_areas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `region_device_areas` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `region_id` int(11) NOT NULL,
  `device_area_id` int(11) NOT NULL,
  `voltage_level_id` int(11) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`region_id`,`device_area_id`),
  KEY `index_region_device_areas_on_region_id` (`region_id`),
  KEY `index_region_device_areas_on_device_area_id` (`device_area_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `regions`
--

DROP TABLE IF EXISTS `regions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `regions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `notes` varchar(255) DEFAULT NULL,
  `seq_no` int(11) DEFAULT NULL,
  `parent_id` int(11) NOT NULL DEFAULT '0',
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`parent_id`,`name`),
  KEY `index_regions_on_name` (`name`),
  KEY `index_regions_on_parent_id` (`parent_id`)
) ENGINE=InnoDB AUTO_INCREMENT=200 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `report_templates`
--

DROP TABLE IF EXISTS `report_templates`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `report_templates` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `order_by1` varchar(255) DEFAULT NULL,
  `order_by2` varchar(255) DEFAULT NULL,
  `order_by3` varchar(255) DEFAULT NULL,
  `order_by4` varchar(255) DEFAULT NULL,
  `order_by5` varchar(255) DEFAULT NULL,
  `order_by6` varchar(255) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  `cover_file_name` varchar(255) DEFAULT NULL,
  `cover_content_type` varchar(255) DEFAULT NULL,
  `cover_file_size` int(11) DEFAULT NULL,
  `cover_updated_at` datetime DEFAULT NULL,
  `preface_file_name` varchar(255) DEFAULT NULL,
  `preface_content_type` varchar(255) DEFAULT NULL,
  `preface_file_size` int(11) DEFAULT NULL,
  `preface_updated_at` datetime DEFAULT NULL,
  `contents_file_name` varchar(255) DEFAULT NULL,
  `contents_content_type` varchar(255) DEFAULT NULL,
  `contents_file_size` int(11) DEFAULT NULL,
  `contents_updated_at` datetime DEFAULT NULL,
  `page_header_file_name` varchar(255) DEFAULT NULL,
  `page_header_content_type` varchar(255) DEFAULT NULL,
  `page_header_file_size` int(11) DEFAULT NULL,
  `page_header_updated_at` datetime DEFAULT NULL,
  `page_footer_file_name` varchar(255) DEFAULT NULL,
  `page_footer_content_type` varchar(255) DEFAULT NULL,
  `page_footer_file_size` int(11) DEFAULT NULL,
  `page_footer_updated_at` datetime DEFAULT NULL,
  `detail_file_name` varchar(255) DEFAULT NULL,
  `detail_content_type` varchar(255) DEFAULT NULL,
  `detail_file_size` int(11) DEFAULT NULL,
  `detail_updated_at` datetime DEFAULT NULL,
  `back_cover_file_name` varchar(255) DEFAULT NULL,
  `back_cover_content_type` varchar(255) DEFAULT NULL,
  `back_cover_file_size` int(11) DEFAULT NULL,
  `back_cover_updated_at` datetime DEFAULT NULL,
  `cover_md5` varchar(32) DEFAULT NULL,
  `preface_md5` varchar(32) DEFAULT NULL,
  `contents_md5` varchar(32) DEFAULT NULL,
  `page_header_md5` varchar(32) DEFAULT NULL,
  `page_footer_md5` varchar(32) DEFAULT NULL,
  `detail_md5` varchar(32) DEFAULT NULL,
  `back_cover_md5` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_report_templates_on_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `shoot_sequences`
--

DROP TABLE IF EXISTS `shoot_sequences`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `shoot_sequences` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `substation_id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL DEFAULT '',
  `notes` text,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`substation_id`,`name`),
  KEY `index_shoot_sequences_on_substation_id` (`substation_id`),
  KEY `index_shoot_sequences_on_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=235 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `slides`
--

DROP TABLE IF EXISTS `slides`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `slides` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `image` varchar(255) DEFAULT NULL,
  `thumb` varchar(255) DEFAULT NULL,
  `big` varchar(255) DEFAULT NULL,
  `title` varchar(255) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `substations`
--

DROP TABLE IF EXISTS `substations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `substations` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `region_id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL DEFAULT '',
  `voltage_level_id` int(11) NOT NULL,
  `notes` varchar(255) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_index` (`region_id`,`name`,`voltage_level_id`),
  KEY `index_substations_on_region_id` (`region_id`),
  KEY `index_substations_on_voltage_level_id` (`voltage_level_id`),
  KEY `index_substations_on_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=1826 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `third_applications`
--

DROP TABLE IF EXISTS `third_applications`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `third_applications` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `app_key` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `callback` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cert_key` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_third_applications_on_app_key_and_cert_key` (`app_key`,`cert_key`),
  KEY `index_third_applications_on_app_key` (`app_key`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `venders`
--

DROP TABLE IF EXISTS `venders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `venders` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `tel` varchar(255) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_venders_on_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=999 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `voltage_levels`
--

DROP TABLE IF EXISTS `voltage_levels`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `voltage_levels` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `notes` varchar(255) DEFAULT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_voltage_levels_on_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=38 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-08-13 15:15:35
