# 
# Synthesis run script generated by Vivado
# 

set TIME_start [clock seconds] 
proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
set_param chipscope.maxJobs 3
set_param xicom.use_bs_reader 1
create_project -in_memory -part xc7a35tcsg324-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.cache/wt [current_project]
set_property parent.project_path C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.xpr [current_project]
set_property XPM_LIBRARIES {XPM_CDC XPM_MEMORY} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property ip_output_repo c:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
add_files C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soft/inst_ram.coe
add_files C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soft/1.coe
add_files C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soft/SwTest.coe
add_files C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soft/addTest.coe
add_files C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soft/non.coe
add_files C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soft/Test_BEQ.coe
add_files C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soft/Test_branch.coe
add_files C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soft/Interface.coe
add_files C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soft/newInterface.coe
add_files C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soft/newBeeInterface.coe
read_verilog C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/macros.vh
read_verilog -library xil_defaultlib {
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/alu.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/br.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/sources_1/new/bridge/bridge_1x2.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/sources_1/new/confreg/confeg.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/cu.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/dmem.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/dmemreq.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/ex2mem.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/id2ex.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/if2id.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/imem.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/mem2wb.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/mmu.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/mycpu_top.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/pc2if.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/regfile.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/core/vga.v
  C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/sources_1/new/teach_soc_top.v
}
read_ip -quiet C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/sources_1/ip/data_ram/data_ram.xci
set_property used_in_implementation false [get_files -all c:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/sources_1/ip/data_ram/data_ram_ooc.xdc]

read_ip -quiet C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/sources_1/ip/inst_ram/inst_ram.xci
set_property used_in_implementation false [get_files -all c:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/sources_1/ip/inst_ram/inst_ram_ooc.xdc]

read_ip -quiet C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/sources_1/ip/clk_pll/clk_pll.xci
set_property used_in_implementation false [get_files -all c:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/sources_1/ip/clk_pll/clk_pll_board.xdc]
set_property used_in_implementation false [get_files -all c:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/sources_1/ip/clk_pll/clk_pll.xdc]
set_property used_in_implementation false [get_files -all c:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/sources_1/ip/clk_pll/clk_pll_ooc.xdc]

# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/constrs_1/new/teach_soc.xdc
set_property used_in_implementation false [get_files C:/Users/27340/Desktop/Composition-principle-and-assembly-Team/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/constrs_1/new/teach_soc.xdc]

set_param ips.enableIPCacheLiteLoad 1
close [open __synthesis_is_running__ w]

synth_design -top teach_soc_top -part xc7a35tcsg324-1


# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef teach_soc_top.dcp
create_report "synth_1_synth_report_utilization_0" "report_utilization -file teach_soc_top_utilization_synth.rpt -pb teach_soc_top_utilization_synth.pb"
file delete __synthesis_is_running__
close [open __synthesis_is_complete__ w]
