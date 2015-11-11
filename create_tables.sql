CREATE TABLE trans_type (
t_type CHAR(32) NOT NULL PRIMARY KEY
);

INSERT INTO trans_type VALUES('ec');

CREATE TABLE trans_request (
r_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
r_type CHAR(32) NOT NULL REFERENCES trans_type( t_type ),
r_origin TEXT NOT NULL COLLATE NOCASE,
UNIQUE(r_type, r_origin)
);

CREATE TABLE trans_result (
r_id REFERENCES trans_request(r_id) ,
r_result TEXT
) ;
