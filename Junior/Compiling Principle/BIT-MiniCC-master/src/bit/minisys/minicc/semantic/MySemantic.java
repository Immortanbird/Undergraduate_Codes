package bit.minisys.minicc.semantic;

import bit.minisys.minicc.parser.ast.*;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.*;

public class MySemantic implements IMiniCCSemantic{
    public String run(String iFile) throws Exception{
        ObjectMapper mapper = new ObjectMapper();
        ASTCompilationUnit program = mapper.readValue(new File(iFile), ASTCompilationUnit.class);

        MySemanticAnalyzer semanticAnalyzer = new MySemanticAnalyzer();
        semanticAnalyzer.visit(program);

        System.out.println(semanticAnalyzer.getErrorInfo());

        System.out.println("4. Semantic finished!");

        return iFile;
    }
}
