package bit.minisys.minicc.icgen;

import bit.minisys.minicc.MiniCCCfg;
import bit.minisys.minicc.internal.util.MiniCCUtil;
import bit.minisys.minicc.parser.ast.ASTCompilationUnit;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.File;

public class MyICGen implements IMiniCCICGen {
    @Override
    public String run(String iFile) throws Exception {
        ObjectMapper mapper = new ObjectMapper();
        ASTCompilationUnit program = mapper.readValue(new File(iFile), ASTCompilationUnit.class);

        String oFile = MiniCCUtil.remove2Ext(iFile) + MiniCCCfg.MINICC_ICGEN_OUTPUT_EXT;

        MyICBuilder icBuilder = new MyICBuilder();
        icBuilder.visit(program);
        MyICPrinter icPrinter = new MyICPrinter(icBuilder.getQuats());
        icPrinter.print(oFile);

        System.out.println("5. Icgen finished!");

        return oFile;
    }
}
