using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Project_Beta
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /*当输入的学号发生改变时，查询并更新数据集等组件*/
        private void SnoTextBox_TextChanged(object sender, EventArgs e)
        {
            HintLabel.Text = "";

            if (SnoTextBox.Text == "")
            {
                NameLabel.Text = "无";
                PointLabel.Text = "0";
                CountLabel.Text = "0";
                ChosenDataSet.Clear();
                LessonDataSet.Chosen.Clear();
                LessonDataSet.Available.Clear();
                return;
            }

            StuDataAdapter.SelectCommand.Parameters.Clear();
            StuDataAdapter.SelectCommand.Parameters.AddWithValue("@Sno", SnoTextBox.Text);
            StuDataSet.Clear();
            StuDataAdapter.Fill(StuDataSet);

            if (!CheckValidOption())
                return;
            else
            {
                NameLabel.Text = StuDataSet.Tables["Stu"].Rows[0]["Sname"].ToString();

                ChosenDataAdapter.SelectCommand.Parameters.Clear();
                ChosenDataAdapter.SelectCommand.Parameters.AddWithValue("@Sno", SnoTextBox.Text);
                ChosenDataSet.Clear();
                ChosenDataAdapter.Fill(ChosenDataSet);

                LessonDataSet.Chosen.Clear();
                LessonDataSet.Available.Clear();

                foreach (DataRow row in LessonDataSet.Lesson)
                    if (ChosenDataSet.Chosen.Select("Lno = '" + row["Lno"].ToString() + "'").Length > 0)
                    {
                        DataRow temp = LessonDataSet.Chosen.NewRow();
                        temp["Lno"] = row["Lno"];
                        temp["Lname"] = row["Lname"];
                        temp["Teacher"] = row["Teacher"];
                        temp["LessonTime"] = row["LessonTime"];
                        temp["Point"] = row["Point"];
                        LessonDataSet.Chosen.Rows.Add(temp);
                    }
                    else
                    {
                        DataRow temp = LessonDataSet.Available.NewRow();
                        temp["Lno"] = row["Lno"];
                        temp["Lname"] = row["Lname"];
                        temp["Teacher"] = row["Teacher"];
                        temp["LessonTime"] = row["LessonTime"];
                        temp["Point"] = row["Point"];
                        LessonDataSet.Available.Rows.Add(temp);
                    }

                double sum = 0;
                foreach (DataRow row in LessonDataSet.Chosen)
                    sum += Convert.ToDouble(row["Point"]);

                PointLabel.Text = sum.ToString();
                CountLabel.Text = LessonDataSet.Chosen.Rows.Count.ToString();
            }
        }

        /*初始化全部课程列表*/
        private void Initialize_LessonDataSet(object sender, EventArgs e)
        {
            LessonDataAdapter.Fill(LessonDataSet);
            HintLabel.Text = "";
        }

        /*点击选课按钮后，如果是合法操作，则从可选课程中删除相应课程并添加到已选课程中，同步修改ChosenDataSet.Chosen*/
        private void SelectButton_Click(object sender, EventArgs e)
        {
            HintLabel.Text = "";

            if (!CheckValidOption())
                return;

            if (AvailableDataGridView.RowCount == 0)
                return;

            int index = AvailableDataGridView.CurrentRow.Index;
            double point = Double.Parse(LessonDataSet.Available[index]["Point"].ToString())
                         + Double.Parse(PointLabel.Text);

            DataRow temp = LessonDataSet.Chosen.NewRow();
            temp["Lno"] = LessonDataSet.Available[index]["Lno"];
            temp["Lname"] = LessonDataSet.Available[index]["Lname"];
            temp["Teacher"] = LessonDataSet.Available[index]["Teacher"];
            temp["LessonTime"] = LessonDataSet.Available[index]["LessonTime"];
            temp["Point"] = LessonDataSet.Available[index]["Point"];
            LessonDataSet.Chosen.Rows.Add(temp);

            DataRow row = ChosenDataSet.Chosen.NewRow();
            row["Sno"] = Int32.Parse(SnoTextBox.Text);
            row["Lno"] = LessonDataSet.Available.Rows[index]["Lno"];
            ChosenDataSet.Chosen.Rows.Add(row);

            LessonDataSet.Available.Rows[index].Delete();

            PointLabel.Text = point.ToString();
            CountLabel.Text = (Int32.Parse(CountLabel.Text) + 1).ToString();
        }

        /*点击退选按钮后，如果是合法操作，则从已选课程中删除相应课程并添加到可选课程中，同步修改ChosenDataSet.Chosen*/
        private void DeleteButton_Click(object sender, EventArgs e)
        {
            HintLabel.Text = "";

            if (!CheckValidOption())
                return;

            if (ChosenDataGridView.RowCount == 0)
                return;

            int index = ChosenDataGridView.CurrentRow.Index;
            double point = Double.Parse(PointLabel.Text)
                         - Double.Parse(LessonDataSet.Chosen[index]["Point"].ToString());

            DataRow temp = LessonDataSet.Available.NewRow();
            temp["Lno"] = LessonDataSet.Chosen[index]["Lno"];
            temp["Lname"] = LessonDataSet.Chosen[index]["Lname"];
            temp["Teacher"] = LessonDataSet.Chosen[index]["Teacher"];
            temp["LessonTime"] = LessonDataSet.Chosen[index]["LessonTime"];
            temp["Point"] = LessonDataSet.Chosen[index]["Point"];
            LessonDataSet.Available.Rows.Add(temp);

            for (int i=0; i<ChosenDataSet.Chosen.Rows.Count; i++)
                if(ChosenDataSet.Chosen[i]["Lno"].ToString() == LessonDataSet.Chosen[index]["Lno"].ToString())
                {
                    ChosenDataSet.Chosen.Rows[i].Delete();
                    break;
                }

            LessonDataSet.Chosen.Rows[index].Delete();

            PointLabel.Text = point.ToString();
            CountLabel.Text = (Int32.Parse(CountLabel.Text) - 1).ToString();
        }

        private void SubmitButton_Click(object sender, EventArgs e)
        {
            HintLabel.Text = "";

            if (!CheckValidOption())
                return;

            if (!ChosenDataSet.HasChanges())
                return;

            if(Int32.Parse(CountLabel.Text) > 5)
            {
                HintLabel.Text = "最多选择5门！";
                return;
            }

            if (Int32.Parse(CountLabel.Text) < 3)
            {
                HintLabel.Text = "最少选择3门！";
                return;
            }

            if(Double.Parse(PointLabel.Text) > 12)
            {
                HintLabel.Text = "最多选择12学分！";
                return;
            }

            if(Double.Parse(PointLabel.Text) < 8)
            {
                HintLabel.Text = "最少选择8学分！";
                return;
            }

            ChosenDataAdapter.Update(ChosenDataSet, "Chosen");

            HintLabel.Text = "选课成功！";
        }

        private void RestoreButton_Click(object sender, EventArgs e)
        {
            HintLabel.Text = "";

            if (!CheckValidOption())
                return;

            if (!ChosenDataSet.HasChanges())
                return;

            ChosenDataSet.Clear();
            ChosenDataAdapter.Fill(ChosenDataSet);

            LessonDataSet.Chosen.Clear();
            LessonDataSet.Available.Clear();

            foreach (DataRow row in LessonDataSet.Lesson)
                if (ChosenDataSet.Chosen.Select("Lno = '" + row["Lno"].ToString() + "'").Length > 0)
                {
                    DataRow temp = LessonDataSet.Chosen.NewRow();
                    temp["Lno"] = row["Lno"];
                    temp["Lname"] = row["Lname"];
                    temp["Teacher"] = row["Teacher"];
                    temp["LessonTime"] = row["LessonTime"];
                    temp["Point"] = row["Point"];
                    LessonDataSet.Chosen.Rows.Add(temp);
                }
                else
                {
                    DataRow temp = LessonDataSet.Available.NewRow();
                    temp["Lno"] = row["Lno"];
                    temp["Lname"] = row["Lname"];
                    temp["Teacher"] = row["Teacher"];
                    temp["LessonTime"] = row["LessonTime"];
                    temp["Point"] = row["Point"];
                    LessonDataSet.Available.Rows.Add(temp);
                }

            double sum = 0;
            foreach (DataRow row in LessonDataSet.Chosen)
                sum += Convert.ToDouble(row["Point"]);

            PointLabel.Text = sum.ToString();
            CountLabel.Text = LessonDataSet.Chosen.Rows.Count.ToString();

            HintLabel.Text = "更改已撤销！";
        }

        /*限制学号输入框的内容为数字和backspace*/ 
        private void KeyPressConstraint(object sender, KeyPressEventArgs e)
        {
            if (!(e.KeyChar == '\b' || char.IsDigit(e.KeyChar)))
                e.Handled = true;
        }

        /*在用户操作触发的事件函数中调用，以判断是否是合理操作*/
        private bool CheckValidOption()
        {
            if (StuDataSet.Stu.Rows.Count == 0)
            {
                NameLabel.Text = "无";
                PointLabel.Text = "0";
                CountLabel.Text = "0";
                ChosenDataSet.Clear();
                LessonDataSet.Chosen.Clear();
                LessonDataSet.Available.Clear();
                return false;
            }
            else
                return true;
        }
    }
}