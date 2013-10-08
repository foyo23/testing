Begin Transaction;
Drop Table If Exists [regions];
CREATE TABLE [regions] (
  [id] INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, 
  [parent_id] INT NOT NULL, 
  [name] TEXT NOT NULL, 
  [notes] TEXT, 
  [basic_type_id] INT, 
  [level] INT, 
  [is_leaf] BOOLEAN, 
  [shoot_sequence_num] INT, 
  [standard_ir_file_name] TEXT, 
  [standard_ir_content_type] CHAR, 
  [standard_ir_file_size] INT, 
  [standard_ir_updated_at] DATETIME, 
  [standard_ir_md5] [TEXT(32)], 
  [standard_ir_unsatisfy] BOOLEAN, 
  UNIQUE([parent_id], [name]));
Commit Transaction;
