CREATE TABLE `basic_subtypes` (`id` int(11) DEFAULT NULL auto_increment PRIMARY KEY, `device_type_id` int(11) NOT NULL, `voltage_level_id` int(11) NOT NULL, `name` varchar(50) NOT NULL, `created_at` datetime NOT NULL, `updated_at` datetime NOT NULL) ENGINE=InnoDB;
CREATE INDEX `index_basic_subtypes_on_voltage_level_id` ON `basic_subtypes` (`voltage_level_id`);
CREATE INDEX `index_basic_subtypes_on_device_type_id` ON `basic_subtypes` (`device_type_id`);
CREATE UNIQUE INDEX `unique_index` ON `basic_subtypes` (`device_type_id`, `voltage_level_id`, `name`);

CREATE TABLE `model_style_standards` (`id` int(11) DEFAULT NULL auto_increment PRIMARY KEY, `model_style_id` int(11) NOT NULL, `part_position_id` int(11) NOT NULL, `standard_ir_file_name` varchar(255), `standard_ir_content_type` varchar(255), `standard_ir_file_size` int(11), `standard_ir_updated_at` datetime, `standard_vi_file_name` varchar(255), `standard_vi_content_type` varchar(255), `standard_vi_file_size` int(11), `standard_vi_updated_at` datetime, `standard_ir_md5` varchar(32), `standard_vi_md5` varchar(32), `standard_ir_unsatisfy` tinyint(1) DEFAULT 0, `standard_vi_unsatisfy` tinyint(1) DEFAULT 0, `created_at` datetime NOT NULL, `updated_at` datetime NOT NULL) ENGINE=InnoDB;
CREATE INDEX `index_standard_ir_updated_at` ON `model_style_standards` (`standard_ir_updated_at`);

CREATE TABLE `model_style_part_positions` (`id` int(11) DEFAULT NULL auto_increment PRIMARY KEY, `model_style_id` int(11) NOT NULL, `part_position_id` int(11) NOT NULL, `basic_subtype_id` int(11) NOT NULL) ENGINE=InnoDB;
CREATE INDEX `index_model_style_part_positions_on_model_style_id` ON `model_style_part_positions` (`model_style_id`);
CREATE INDEX `index_model_style_part_positions_on_part_position_id` ON `model_style_part_positions` (`part_position_id`);
CREATE INDEX `index_model_style_part_positions_on_basic_subtype_id` ON `model_style_part_positions` (`basic_subtype_id`);
CREATE UNIQUE INDEX `unique_index` ON `model_style_part_positions` (`model_style_id`, `part_position_id`, `basic_subtype_id`);

ALTER TABLE `outlines` DROP `standard_ir_file_name`;
ALTER TABLE `outlines` DROP `standard_ir_content_type`;
ALTER TABLE `outlines` DROP `standard_ir_file_size`;
ALTER TABLE `outlines` DROP `standard_ir_updated_at`;
ALTER TABLE `outlines` DROP `standard_vi_file_name`;
ALTER TABLE `outlines` DROP `standard_vi_content_type`;
ALTER TABLE `outlines` DROP `standard_vi_file_size`;
ALTER TABLE `outlines` DROP `standard_vi_updated_at`;
ALTER TABLE `outlines` DROP `standard_ir_md5`;
ALTER TABLE `outlines` DROP `standard_vi_md5`;
ALTER TABLE `outlines` DROP `standard_ir_unsatisfy`;
ALTER TABLE `outlines` DROP `standard_vi_unsatisfy`;
DROP INDEX `unique_index` ON `outlines`;
DROP INDEX `index_outlines_on_model_style_id` ON `outlines`;
DROP INDEX `index_outlines_on_part_position_id` ON `outlines`;
ALTER TABLE `outlines` ADD `basic_subtype_id` int(11) NOT NULL AFTER `part_position_id`;
--增加一个数据本身迁移语句
CREATE UNIQUE INDEX `index_basic_subtype_id` ON `outlines` (`basic_subtype_id`);
