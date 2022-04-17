
namespace Project_Beta
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.PorojectDBConnection = new System.Data.SqlClient.SqlConnection();
            this.sqlSelectCommand1 = new System.Data.SqlClient.SqlCommand();
            this.sqlInsertCommand1 = new System.Data.SqlClient.SqlCommand();
            this.sqlUpdateCommand1 = new System.Data.SqlClient.SqlCommand();
            this.sqlDeleteCommand1 = new System.Data.SqlClient.SqlCommand();
            this.StuDataAdapter = new System.Data.SqlClient.SqlDataAdapter();
            this.StuDataSet = new Project_Beta.StuDataSet();
            this.sqlSelectCommand2 = new System.Data.SqlClient.SqlCommand();
            this.sqlInsertCommand2 = new System.Data.SqlClient.SqlCommand();
            this.sqlDeleteCommand2 = new System.Data.SqlClient.SqlCommand();
            this.ChosenDataAdapter = new System.Data.SqlClient.SqlDataAdapter();
            this.chosenBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.LessonDataSet = new Project_Beta.LessonDataSet();
            this.label5 = new System.Windows.Forms.Label();
            this.AvailableDataGridView = new System.Windows.Forms.DataGridView();
            this.lnoDataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.lnameDataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.teacherDataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.lessonTimeDataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.pointDataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.availableBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.sqlSelectCommand3 = new System.Data.SqlClient.SqlCommand();
            this.sqlInsertCommand3 = new System.Data.SqlClient.SqlCommand();
            this.sqlUpdateCommand2 = new System.Data.SqlClient.SqlCommand();
            this.sqlDeleteCommand3 = new System.Data.SqlClient.SqlCommand();
            this.LessonDataAdapter = new System.Data.SqlClient.SqlDataAdapter();
            this.ChosenDataSet = new Project_Beta.ChosenDataSet();
            this.SelectButton = new System.Windows.Forms.Button();
            this.headline = new System.Windows.Forms.Label();
            this.NameLabel = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SnoTextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.HintLabel = new System.Windows.Forms.Label();
            this.ChosenDataGridView = new System.Windows.Forms.DataGridView();
            this.lnoDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.lnameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.teacherDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.lessonTimeDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.pointDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.label3 = new System.Windows.Forms.Label();
            this.DeleteButton = new System.Windows.Forms.Button();
            this.SubmitButton = new System.Windows.Forms.Button();
            this.RestoreButton = new System.Windows.Forms.Button();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.CountLabel = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.PointLabel = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.StuDataSet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chosenBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.LessonDataSet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AvailableDataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.availableBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ChosenDataSet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ChosenDataGridView)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // PorojectDBConnection
            // 
            this.PorojectDBConnection.ConnectionString = "Data Source=.;Initial Catalog=ProjectDB;Integrated Security=True";
            this.PorojectDBConnection.FireInfoMessageEventOnUserErrors = false;
            // 
            // sqlSelectCommand1
            // 
            this.sqlSelectCommand1.CommandText = "SELECT Sno, Sname\r\nFROM   Stu\r\nWHERE (Sno = @Sno)";
            this.sqlSelectCommand1.Connection = this.PorojectDBConnection;
            this.sqlSelectCommand1.Parameters.AddRange(new System.Data.SqlClient.SqlParameter[] {
            new System.Data.SqlClient.SqlParameter("@Sno", System.Data.SqlDbType.Int, 4, "Sno")});
            // 
            // sqlInsertCommand1
            // 
            this.sqlInsertCommand1.CommandText = "INSERT INTO [Stu] ([Sno], [Sname]) VALUES (@Sno, @Sname);\r\nSELECT Sno, Sname FROM" +
    " Stu WHERE (Sno = @Sno)";
            this.sqlInsertCommand1.Connection = this.PorojectDBConnection;
            this.sqlInsertCommand1.Parameters.AddRange(new System.Data.SqlClient.SqlParameter[] {
            new System.Data.SqlClient.SqlParameter("@Sno", System.Data.SqlDbType.Int, 0, "Sno"),
            new System.Data.SqlClient.SqlParameter("@Sname", System.Data.SqlDbType.VarChar, 0, "Sname")});
            // 
            // sqlUpdateCommand1
            // 
            this.sqlUpdateCommand1.CommandText = "UPDATE [Stu] SET [Sno] = @Sno, [Sname] = @Sname WHERE (([Sno] = @Original_Sno) AN" +
    "D ([Sname] = @Original_Sname));\r\nSELECT Sno, Sname FROM Stu WHERE (Sno = @Sno)";
            this.sqlUpdateCommand1.Connection = this.PorojectDBConnection;
            this.sqlUpdateCommand1.Parameters.AddRange(new System.Data.SqlClient.SqlParameter[] {
            new System.Data.SqlClient.SqlParameter("@Sno", System.Data.SqlDbType.Int, 0, "Sno"),
            new System.Data.SqlClient.SqlParameter("@Sname", System.Data.SqlDbType.VarChar, 0, "Sname"),
            new System.Data.SqlClient.SqlParameter("@Original_Sno", System.Data.SqlDbType.Int, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Sno", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@Original_Sname", System.Data.SqlDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Sname", System.Data.DataRowVersion.Original, null)});
            // 
            // sqlDeleteCommand1
            // 
            this.sqlDeleteCommand1.CommandText = "DELETE FROM [Stu] WHERE (([Sno] = @Original_Sno) AND ([Sname] = @Original_Sname))" +
    "";
            this.sqlDeleteCommand1.Connection = this.PorojectDBConnection;
            this.sqlDeleteCommand1.Parameters.AddRange(new System.Data.SqlClient.SqlParameter[] {
            new System.Data.SqlClient.SqlParameter("@Original_Sno", System.Data.SqlDbType.Int, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Sno", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@Original_Sname", System.Data.SqlDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Sname", System.Data.DataRowVersion.Original, null)});
            // 
            // StuDataAdapter
            // 
            this.StuDataAdapter.DeleteCommand = this.sqlDeleteCommand1;
            this.StuDataAdapter.InsertCommand = this.sqlInsertCommand1;
            this.StuDataAdapter.SelectCommand = this.sqlSelectCommand1;
            this.StuDataAdapter.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
            new System.Data.Common.DataTableMapping("Table", "Stu", new System.Data.Common.DataColumnMapping[] {
                        new System.Data.Common.DataColumnMapping("Sno", "Sno"),
                        new System.Data.Common.DataColumnMapping("Sname", "Sname")})});
            this.StuDataAdapter.UpdateCommand = this.sqlUpdateCommand1;
            // 
            // StuDataSet
            // 
            this.StuDataSet.DataSetName = "StuDataSet";
            this.StuDataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // sqlSelectCommand2
            // 
            this.sqlSelectCommand2.CommandText = "SELECT Chosen.*\r\nFROM   Chosen\r\nWHERE (Sno = @Sno)";
            this.sqlSelectCommand2.Connection = this.PorojectDBConnection;
            this.sqlSelectCommand2.Parameters.AddRange(new System.Data.SqlClient.SqlParameter[] {
            new System.Data.SqlClient.SqlParameter("@Sno", System.Data.SqlDbType.Int, 4, "Sno")});
            // 
            // sqlInsertCommand2
            // 
            this.sqlInsertCommand2.CommandText = "INSERT INTO [Chosen] ([Sno], [Lno]) VALUES (@Sno, @Lno)";
            this.sqlInsertCommand2.Connection = this.PorojectDBConnection;
            this.sqlInsertCommand2.Parameters.AddRange(new System.Data.SqlClient.SqlParameter[] {
            new System.Data.SqlClient.SqlParameter("@Sno", System.Data.SqlDbType.Int, 0, "Sno"),
            new System.Data.SqlClient.SqlParameter("@Lno", System.Data.SqlDbType.Int, 0, "Lno")});
            // 
            // sqlDeleteCommand2
            // 
            this.sqlDeleteCommand2.CommandText = resources.GetString("sqlDeleteCommand2.CommandText");
            this.sqlDeleteCommand2.Connection = this.PorojectDBConnection;
            this.sqlDeleteCommand2.Parameters.AddRange(new System.Data.SqlClient.SqlParameter[] {
            new System.Data.SqlClient.SqlParameter("@Original_Lno", System.Data.SqlDbType.Int, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Lno", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@Original_Lname", System.Data.SqlDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Lname", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@Original_Teacher", System.Data.SqlDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Teacher", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@IsNull_LessonTime", System.Data.SqlDbType.Int, 0, System.Data.ParameterDirection.Input, ((byte)(0)), ((byte)(0)), "LessonTime", System.Data.DataRowVersion.Original, true, null, "", "", ""),
            new System.Data.SqlClient.SqlParameter("@Original_LessonTime", System.Data.SqlDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "LessonTime", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@IsNull_Point", System.Data.SqlDbType.Int, 0, System.Data.ParameterDirection.Input, ((byte)(0)), ((byte)(0)), "Point", System.Data.DataRowVersion.Original, true, null, "", "", ""),
            new System.Data.SqlClient.SqlParameter("@Original_Point", System.Data.SqlDbType.Float, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Point", System.Data.DataRowVersion.Original, null)});
            // 
            // ChosenDataAdapter
            // 
            this.ChosenDataAdapter.DeleteCommand = this.sqlDeleteCommand2;
            this.ChosenDataAdapter.InsertCommand = this.sqlInsertCommand2;
            this.ChosenDataAdapter.SelectCommand = this.sqlSelectCommand2;
            this.ChosenDataAdapter.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
            new System.Data.Common.DataTableMapping("Table", "Chosen", new System.Data.Common.DataColumnMapping[] {
                        new System.Data.Common.DataColumnMapping("Sno", "Sno"),
                        new System.Data.Common.DataColumnMapping("Lno", "Lno")})});
            // 
            // chosenBindingSource
            // 
            this.chosenBindingSource.DataMember = "Chosen";
            this.chosenBindingSource.DataSource = this.LessonDataSet;
            // 
            // LessonDataSet
            // 
            this.LessonDataSet.DataSetName = "LessonDataSet";
            this.LessonDataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            this.LessonDataSet.Initialized += new System.EventHandler(this.Initialize_LessonDataSet);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label5.Location = new System.Drawing.Point(107, 184);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(229, 71);
            this.label5.TabIndex = 10;
            this.label5.Text = "可选课程：";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // AvailableDataGridView
            // 
            this.AvailableDataGridView.AllowUserToAddRows = false;
            this.AvailableDataGridView.AllowUserToDeleteRows = false;
            this.AvailableDataGridView.AutoGenerateColumns = false;
            this.AvailableDataGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.AvailableDataGridView.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.DisplayedCells;
            this.AvailableDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.AvailableDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.lnoDataGridViewTextBoxColumn1,
            this.lnameDataGridViewTextBoxColumn1,
            this.teacherDataGridViewTextBoxColumn1,
            this.lessonTimeDataGridViewTextBoxColumn1,
            this.pointDataGridViewTextBoxColumn1});
            this.tableLayoutPanel1.SetColumnSpan(this.AvailableDataGridView, 8);
            this.AvailableDataGridView.DataSource = this.availableBindingSource;
            this.AvailableDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AvailableDataGridView.Location = new System.Drawing.Point(107, 258);
            this.AvailableDataGridView.MultiSelect = false;
            this.AvailableDataGridView.Name = "AvailableDataGridView";
            this.AvailableDataGridView.ReadOnly = true;
            this.AvailableDataGridView.RowHeadersWidth = 82;
            this.AvailableDataGridView.RowTemplate.Height = 37;
            this.AvailableDataGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.AvailableDataGridView.Size = new System.Drawing.Size(1874, 448);
            this.AvailableDataGridView.TabIndex = 13;
            // 
            // lnoDataGridViewTextBoxColumn1
            // 
            this.lnoDataGridViewTextBoxColumn1.DataPropertyName = "Lno";
            this.lnoDataGridViewTextBoxColumn1.HeaderText = "Lno";
            this.lnoDataGridViewTextBoxColumn1.MinimumWidth = 10;
            this.lnoDataGridViewTextBoxColumn1.Name = "lnoDataGridViewTextBoxColumn1";
            this.lnoDataGridViewTextBoxColumn1.ReadOnly = true;
            // 
            // lnameDataGridViewTextBoxColumn1
            // 
            this.lnameDataGridViewTextBoxColumn1.DataPropertyName = "Lname";
            this.lnameDataGridViewTextBoxColumn1.HeaderText = "Lname";
            this.lnameDataGridViewTextBoxColumn1.MinimumWidth = 10;
            this.lnameDataGridViewTextBoxColumn1.Name = "lnameDataGridViewTextBoxColumn1";
            this.lnameDataGridViewTextBoxColumn1.ReadOnly = true;
            // 
            // teacherDataGridViewTextBoxColumn1
            // 
            this.teacherDataGridViewTextBoxColumn1.DataPropertyName = "Teacher";
            this.teacherDataGridViewTextBoxColumn1.HeaderText = "Teacher";
            this.teacherDataGridViewTextBoxColumn1.MinimumWidth = 10;
            this.teacherDataGridViewTextBoxColumn1.Name = "teacherDataGridViewTextBoxColumn1";
            this.teacherDataGridViewTextBoxColumn1.ReadOnly = true;
            // 
            // lessonTimeDataGridViewTextBoxColumn1
            // 
            this.lessonTimeDataGridViewTextBoxColumn1.DataPropertyName = "LessonTime";
            this.lessonTimeDataGridViewTextBoxColumn1.HeaderText = "LessonTime";
            this.lessonTimeDataGridViewTextBoxColumn1.MinimumWidth = 10;
            this.lessonTimeDataGridViewTextBoxColumn1.Name = "lessonTimeDataGridViewTextBoxColumn1";
            this.lessonTimeDataGridViewTextBoxColumn1.ReadOnly = true;
            // 
            // pointDataGridViewTextBoxColumn1
            // 
            this.pointDataGridViewTextBoxColumn1.DataPropertyName = "Point";
            this.pointDataGridViewTextBoxColumn1.HeaderText = "Point";
            this.pointDataGridViewTextBoxColumn1.MinimumWidth = 10;
            this.pointDataGridViewTextBoxColumn1.Name = "pointDataGridViewTextBoxColumn1";
            this.pointDataGridViewTextBoxColumn1.ReadOnly = true;
            // 
            // availableBindingSource
            // 
            this.availableBindingSource.DataMember = "Available";
            this.availableBindingSource.DataSource = this.LessonDataSet;
            // 
            // sqlSelectCommand3
            // 
            this.sqlSelectCommand3.CommandText = "SELECT Lesson.*\r\nFROM   Lesson";
            this.sqlSelectCommand3.Connection = this.PorojectDBConnection;
            // 
            // sqlInsertCommand3
            // 
            this.sqlInsertCommand3.CommandText = resources.GetString("sqlInsertCommand3.CommandText");
            this.sqlInsertCommand3.Connection = this.PorojectDBConnection;
            this.sqlInsertCommand3.Parameters.AddRange(new System.Data.SqlClient.SqlParameter[] {
            new System.Data.SqlClient.SqlParameter("@Lno", System.Data.SqlDbType.Int, 0, "Lno"),
            new System.Data.SqlClient.SqlParameter("@Lname", System.Data.SqlDbType.VarChar, 0, "Lname"),
            new System.Data.SqlClient.SqlParameter("@Teacher", System.Data.SqlDbType.VarChar, 0, "Teacher"),
            new System.Data.SqlClient.SqlParameter("@LessonTime", System.Data.SqlDbType.VarChar, 0, "LessonTime"),
            new System.Data.SqlClient.SqlParameter("@Point", System.Data.SqlDbType.Float, 0, "Point")});
            // 
            // sqlUpdateCommand2
            // 
            this.sqlUpdateCommand2.CommandText = resources.GetString("sqlUpdateCommand2.CommandText");
            this.sqlUpdateCommand2.Connection = this.PorojectDBConnection;
            this.sqlUpdateCommand2.Parameters.AddRange(new System.Data.SqlClient.SqlParameter[] {
            new System.Data.SqlClient.SqlParameter("@Lno", System.Data.SqlDbType.Int, 0, "Lno"),
            new System.Data.SqlClient.SqlParameter("@Lname", System.Data.SqlDbType.VarChar, 0, "Lname"),
            new System.Data.SqlClient.SqlParameter("@Teacher", System.Data.SqlDbType.VarChar, 0, "Teacher"),
            new System.Data.SqlClient.SqlParameter("@LessonTime", System.Data.SqlDbType.VarChar, 0, "LessonTime"),
            new System.Data.SqlClient.SqlParameter("@Point", System.Data.SqlDbType.Float, 0, "Point"),
            new System.Data.SqlClient.SqlParameter("@Original_Lno", System.Data.SqlDbType.Int, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Lno", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@Original_Lname", System.Data.SqlDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Lname", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@Original_Teacher", System.Data.SqlDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Teacher", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@IsNull_LessonTime", System.Data.SqlDbType.Int, 0, System.Data.ParameterDirection.Input, ((byte)(0)), ((byte)(0)), "LessonTime", System.Data.DataRowVersion.Original, true, null, "", "", ""),
            new System.Data.SqlClient.SqlParameter("@Original_LessonTime", System.Data.SqlDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "LessonTime", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@IsNull_Point", System.Data.SqlDbType.Int, 0, System.Data.ParameterDirection.Input, ((byte)(0)), ((byte)(0)), "Point", System.Data.DataRowVersion.Original, true, null, "", "", ""),
            new System.Data.SqlClient.SqlParameter("@Original_Point", System.Data.SqlDbType.Float, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Point", System.Data.DataRowVersion.Original, null)});
            // 
            // sqlDeleteCommand3
            // 
            this.sqlDeleteCommand3.CommandText = resources.GetString("sqlDeleteCommand3.CommandText");
            this.sqlDeleteCommand3.Connection = this.PorojectDBConnection;
            this.sqlDeleteCommand3.Parameters.AddRange(new System.Data.SqlClient.SqlParameter[] {
            new System.Data.SqlClient.SqlParameter("@Original_Lno", System.Data.SqlDbType.Int, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Lno", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@Original_Lname", System.Data.SqlDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Lname", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@Original_Teacher", System.Data.SqlDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Teacher", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@IsNull_LessonTime", System.Data.SqlDbType.Int, 0, System.Data.ParameterDirection.Input, ((byte)(0)), ((byte)(0)), "LessonTime", System.Data.DataRowVersion.Original, true, null, "", "", ""),
            new System.Data.SqlClient.SqlParameter("@Original_LessonTime", System.Data.SqlDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "LessonTime", System.Data.DataRowVersion.Original, null),
            new System.Data.SqlClient.SqlParameter("@IsNull_Point", System.Data.SqlDbType.Int, 0, System.Data.ParameterDirection.Input, ((byte)(0)), ((byte)(0)), "Point", System.Data.DataRowVersion.Original, true, null, "", "", ""),
            new System.Data.SqlClient.SqlParameter("@Original_Point", System.Data.SqlDbType.Float, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "Point", System.Data.DataRowVersion.Original, null)});
            // 
            // LessonDataAdapter
            // 
            this.LessonDataAdapter.DeleteCommand = this.sqlDeleteCommand3;
            this.LessonDataAdapter.InsertCommand = this.sqlInsertCommand3;
            this.LessonDataAdapter.SelectCommand = this.sqlSelectCommand3;
            this.LessonDataAdapter.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
            new System.Data.Common.DataTableMapping("Table", "Lesson", new System.Data.Common.DataColumnMapping[] {
                        new System.Data.Common.DataColumnMapping("Lno", "Lno"),
                        new System.Data.Common.DataColumnMapping("Lname", "Lname"),
                        new System.Data.Common.DataColumnMapping("Teacher", "Teacher"),
                        new System.Data.Common.DataColumnMapping("LessonTime", "LessonTime"),
                        new System.Data.Common.DataColumnMapping("Point", "Point")})});
            this.LessonDataAdapter.UpdateCommand = this.sqlUpdateCommand2;
            // 
            // ChosenDataSet
            // 
            this.ChosenDataSet.DataSetName = "ChosenDataSet";
            this.ChosenDataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // SelectButton
            // 
            this.SelectButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.SelectButton.Location = new System.Drawing.Point(342, 196);
            this.SelectButton.Name = "SelectButton";
            this.SelectButton.Size = new System.Drawing.Size(229, 46);
            this.SelectButton.TabIndex = 14;
            this.SelectButton.Text = "选择";
            this.SelectButton.UseVisualStyleBackColor = true;
            this.SelectButton.Click += new System.EventHandler(this.SelectButton_Click);
            // 
            // headline
            // 
            this.headline.AutoSize = true;
            this.tableLayoutPanel1.SetColumnSpan(this.headline, 2);
            this.headline.Dock = System.Windows.Forms.DockStyle.Fill;
            this.headline.Font = new System.Drawing.Font("楷体", 16.125F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.headline.Location = new System.Drawing.Point(812, 0);
            this.headline.Name = "headline";
            this.headline.Size = new System.Drawing.Size(464, 113);
            this.headline.TabIndex = 0;
            this.headline.Text = "选课系统";
            this.headline.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // NameLabel
            // 
            this.NameLabel.AutoSize = true;
            this.NameLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.NameLabel.Location = new System.Drawing.Point(812, 113);
            this.NameLabel.Name = "NameLabel";
            this.NameLabel.Size = new System.Drawing.Size(229, 71);
            this.NameLabel.TabIndex = 4;
            this.NameLabel.Text = "无";
            this.NameLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label2.Location = new System.Drawing.Point(577, 113);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(229, 71);
            this.label2.TabIndex = 2;
            this.label2.Text = "姓名：";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // SnoTextBox
            // 
            this.SnoTextBox.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.SnoTextBox.Location = new System.Drawing.Point(342, 129);
            this.SnoTextBox.MaxLength = 10;
            this.SnoTextBox.Name = "SnoTextBox";
            this.SnoTextBox.Size = new System.Drawing.Size(221, 39);
            this.SnoTextBox.TabIndex = 3;
            this.SnoTextBox.TextChanged += new System.EventHandler(this.SnoTextBox_TextChanged);
            this.SnoTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.KeyPressConstraint);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label1.Location = new System.Drawing.Point(107, 113);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(229, 71);
            this.label1.TabIndex = 1;
            this.label1.Text = "学号：";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // HintLabel
            // 
            this.HintLabel.AutoSize = true;
            this.HintLabel.CausesValidation = false;
            this.tableLayoutPanel1.SetColumnSpan(this.HintLabel, 2);
            this.HintLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.HintLabel.Font = new System.Drawing.Font("微软雅黑", 13.875F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.HintLabel.ForeColor = System.Drawing.Color.Red;
            this.HintLabel.Location = new System.Drawing.Point(1282, 113);
            this.HintLabel.Name = "HintLabel";
            this.HintLabel.Size = new System.Drawing.Size(464, 71);
            this.HintLabel.TabIndex = 18;
            this.HintLabel.Text = "HintLabel";
            this.HintLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // ChosenDataGridView
            // 
            this.ChosenDataGridView.AllowUserToAddRows = false;
            this.ChosenDataGridView.AllowUserToDeleteRows = false;
            this.ChosenDataGridView.AutoGenerateColumns = false;
            this.ChosenDataGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.ChosenDataGridView.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.ChosenDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ChosenDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.lnoDataGridViewTextBoxColumn,
            this.lnameDataGridViewTextBoxColumn,
            this.teacherDataGridViewTextBoxColumn,
            this.lessonTimeDataGridViewTextBoxColumn,
            this.pointDataGridViewTextBoxColumn});
            this.tableLayoutPanel1.SetColumnSpan(this.ChosenDataGridView, 8);
            this.ChosenDataGridView.DataSource = this.chosenBindingSource;
            this.ChosenDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ChosenDataGridView.Location = new System.Drawing.Point(107, 854);
            this.ChosenDataGridView.MultiSelect = false;
            this.ChosenDataGridView.Name = "ChosenDataGridView";
            this.ChosenDataGridView.ReadOnly = true;
            this.ChosenDataGridView.RowHeadersWidth = 82;
            this.ChosenDataGridView.RowTemplate.Height = 37;
            this.ChosenDataGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.ChosenDataGridView.Size = new System.Drawing.Size(1874, 448);
            this.ChosenDataGridView.TabIndex = 7;
            // 
            // lnoDataGridViewTextBoxColumn
            // 
            this.lnoDataGridViewTextBoxColumn.DataPropertyName = "Lno";
            this.lnoDataGridViewTextBoxColumn.HeaderText = "Lno";
            this.lnoDataGridViewTextBoxColumn.MinimumWidth = 10;
            this.lnoDataGridViewTextBoxColumn.Name = "lnoDataGridViewTextBoxColumn";
            this.lnoDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // lnameDataGridViewTextBoxColumn
            // 
            this.lnameDataGridViewTextBoxColumn.DataPropertyName = "Lname";
            this.lnameDataGridViewTextBoxColumn.HeaderText = "Lname";
            this.lnameDataGridViewTextBoxColumn.MinimumWidth = 10;
            this.lnameDataGridViewTextBoxColumn.Name = "lnameDataGridViewTextBoxColumn";
            this.lnameDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // teacherDataGridViewTextBoxColumn
            // 
            this.teacherDataGridViewTextBoxColumn.DataPropertyName = "Teacher";
            this.teacherDataGridViewTextBoxColumn.HeaderText = "Teacher";
            this.teacherDataGridViewTextBoxColumn.MinimumWidth = 10;
            this.teacherDataGridViewTextBoxColumn.Name = "teacherDataGridViewTextBoxColumn";
            this.teacherDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // lessonTimeDataGridViewTextBoxColumn
            // 
            this.lessonTimeDataGridViewTextBoxColumn.DataPropertyName = "LessonTime";
            this.lessonTimeDataGridViewTextBoxColumn.HeaderText = "LessonTime";
            this.lessonTimeDataGridViewTextBoxColumn.MinimumWidth = 10;
            this.lessonTimeDataGridViewTextBoxColumn.Name = "lessonTimeDataGridViewTextBoxColumn";
            this.lessonTimeDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // pointDataGridViewTextBoxColumn
            // 
            this.pointDataGridViewTextBoxColumn.DataPropertyName = "Point";
            this.pointDataGridViewTextBoxColumn.HeaderText = "Point";
            this.pointDataGridViewTextBoxColumn.MinimumWidth = 10;
            this.pointDataGridViewTextBoxColumn.Name = "pointDataGridViewTextBoxColumn";
            this.pointDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label3.Location = new System.Drawing.Point(107, 780);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(229, 71);
            this.label3.TabIndex = 6;
            this.label3.Text = "已选课程：";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // DeleteButton
            // 
            this.DeleteButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.DeleteButton.Location = new System.Drawing.Point(342, 792);
            this.DeleteButton.Name = "DeleteButton";
            this.DeleteButton.Size = new System.Drawing.Size(229, 46);
            this.DeleteButton.TabIndex = 15;
            this.DeleteButton.Text = "退选";
            this.DeleteButton.UseVisualStyleBackColor = true;
            this.DeleteButton.Click += new System.EventHandler(this.DeleteButton_Click);
            // 
            // SubmitButton
            // 
            this.SubmitButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.SubmitButton.Location = new System.Drawing.Point(812, 1308);
            this.SubmitButton.Name = "SubmitButton";
            this.SubmitButton.Size = new System.Drawing.Size(229, 55);
            this.SubmitButton.TabIndex = 16;
            this.SubmitButton.Text = "提交更改";
            this.SubmitButton.UseVisualStyleBackColor = true;
            this.SubmitButton.Click += new System.EventHandler(this.SubmitButton_Click);
            // 
            // RestoreButton
            // 
            this.RestoreButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.RestoreButton.Location = new System.Drawing.Point(1047, 1308);
            this.RestoreButton.Name = "RestoreButton";
            this.RestoreButton.Size = new System.Drawing.Size(229, 55);
            this.RestoreButton.TabIndex = 17;
            this.RestoreButton.Text = "放弃更改";
            this.RestoreButton.UseVisualStyleBackColor = true;
            this.RestoreButton.Click += new System.EventHandler(this.RestoreButton_Click);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 10;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 5F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 11.25F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 11.25F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 11.25F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 11.25F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 11.25F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 11.25F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 11.25F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 11.25F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 5F));
            this.tableLayoutPanel1.Controls.Add(this.RestoreButton, 5, 7);
            this.tableLayoutPanel1.Controls.Add(this.DeleteButton, 2, 5);
            this.tableLayoutPanel1.Controls.Add(this.SubmitButton, 4, 7);
            this.tableLayoutPanel1.Controls.Add(this.HintLabel, 6, 1);
            this.tableLayoutPanel1.Controls.Add(this.label3, 1, 5);
            this.tableLayoutPanel1.Controls.Add(this.headline, 4, 0);
            this.tableLayoutPanel1.Controls.Add(this.SelectButton, 2, 2);
            this.tableLayoutPanel1.Controls.Add(this.AvailableDataGridView, 1, 3);
            this.tableLayoutPanel1.Controls.Add(this.label5, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.ChosenDataGridView, 1, 6);
            this.tableLayoutPanel1.Controls.Add(this.label1, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.NameLabel, 4, 1);
            this.tableLayoutPanel1.Controls.Add(this.SnoTextBox, 2, 1);
            this.tableLayoutPanel1.Controls.Add(this.label2, 3, 1);
            this.tableLayoutPanel1.Controls.Add(this.CountLabel, 2, 4);
            this.tableLayoutPanel1.Controls.Add(this.label7, 3, 4);
            this.tableLayoutPanel1.Controls.Add(this.PointLabel, 4, 4);
            this.tableLayoutPanel1.Controls.Add(this.label4, 1, 4);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 8;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 8F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 5F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 5F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 32F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 5F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 5F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 32F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 8F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(2092, 1420);
            this.tableLayoutPanel1.TabIndex = 20;
            // 
            // CountLabel
            // 
            this.CountLabel.AutoSize = true;
            this.CountLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.CountLabel.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CountLabel.Location = new System.Drawing.Point(342, 709);
            this.CountLabel.Name = "CountLabel";
            this.CountLabel.Size = new System.Drawing.Size(229, 71);
            this.CountLabel.TabIndex = 20;
            this.CountLabel.Text = "0";
            this.CountLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label7.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.Location = new System.Drawing.Point(577, 709);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(229, 71);
            this.label7.TabIndex = 21;
            this.label7.Text = "已选学分：";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // PointLabel
            // 
            this.PointLabel.AutoSize = true;
            this.PointLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PointLabel.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.PointLabel.Location = new System.Drawing.Point(812, 709);
            this.PointLabel.Name = "PointLabel";
            this.PointLabel.Size = new System.Drawing.Size(229, 71);
            this.PointLabel.TabIndex = 22;
            this.PointLabel.Text = "0";
            this.PointLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label4.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(107, 709);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(229, 71);
            this.label4.TabIndex = 19;
            this.label4.Text = "已选课程数:";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Form1
            // 
            this.AcceptButton = this.SubmitButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(192F, 192F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.AutoSize = true;
            this.BackColor = System.Drawing.SystemColors.Info;
            this.ClientSize = new System.Drawing.Size(2092, 1420);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "选课系统";
            ((System.ComponentModel.ISupportInitialize)(this.StuDataSet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chosenBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.LessonDataSet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AvailableDataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.availableBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ChosenDataSet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ChosenDataGridView)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Data.SqlClient.SqlConnection PorojectDBConnection;
        private System.Data.SqlClient.SqlCommand sqlSelectCommand1;
        private System.Data.SqlClient.SqlCommand sqlInsertCommand1;
        private System.Data.SqlClient.SqlCommand sqlUpdateCommand1;
        private System.Data.SqlClient.SqlCommand sqlDeleteCommand1;
        private System.Data.SqlClient.SqlDataAdapter StuDataAdapter;
        private StuDataSet StuDataSet;
        private System.Data.SqlClient.SqlCommand sqlSelectCommand2;
        private System.Data.SqlClient.SqlCommand sqlInsertCommand2;
        private System.Data.SqlClient.SqlCommand sqlDeleteCommand2;
        private System.Data.SqlClient.SqlDataAdapter ChosenDataAdapter;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.DataGridView AvailableDataGridView;
        private ChosenDataSet ChosenDataSet;
        private System.Data.SqlClient.SqlCommand sqlSelectCommand3;
        private System.Data.SqlClient.SqlCommand sqlInsertCommand3;
        private System.Data.SqlClient.SqlCommand sqlUpdateCommand2;
        private System.Data.SqlClient.SqlCommand sqlDeleteCommand3;
        private System.Data.SqlClient.SqlDataAdapter LessonDataAdapter;
        private LessonDataSet LessonDataSet;
        private System.Windows.Forms.BindingSource chosenBindingSource;
        private System.Windows.Forms.DataGridViewTextBoxColumn lnoDataGridViewTextBoxColumn1;
        private System.Windows.Forms.DataGridViewTextBoxColumn lnameDataGridViewTextBoxColumn1;
        private System.Windows.Forms.DataGridViewTextBoxColumn teacherDataGridViewTextBoxColumn1;
        private System.Windows.Forms.DataGridViewTextBoxColumn lessonTimeDataGridViewTextBoxColumn1;
        private System.Windows.Forms.DataGridViewTextBoxColumn pointDataGridViewTextBoxColumn1;
        private System.Windows.Forms.BindingSource availableBindingSource;
        private System.Windows.Forms.Button SelectButton;
        private System.Windows.Forms.Label HintLabel;
        private System.Windows.Forms.Label headline;
        private System.Windows.Forms.Label NameLabel;
        private System.Windows.Forms.TextBox SnoTextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button DeleteButton;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DataGridView ChosenDataGridView;
        private System.Windows.Forms.DataGridViewTextBoxColumn lnoDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn lnameDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn teacherDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn lessonTimeDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn pointDataGridViewTextBoxColumn;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button SubmitButton;
        private System.Windows.Forms.Button RestoreButton;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label CountLabel;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label PointLabel;
        private System.Windows.Forms.Label label4;
    }
}

