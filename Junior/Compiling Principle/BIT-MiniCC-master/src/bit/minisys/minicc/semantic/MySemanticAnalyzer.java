package bit.minisys.minicc.semantic;

import bit.minisys.minicc.parser.ast.*;

import java.util.List;
import java.util.*;

@SuppressWarnings("SpellCheckingInspection")
public class MySemanticAnalyzer {
    private List<VarTable> GlobalVarTable = new LinkedList<>();
    private List<FuncTable> ProcTable = new LinkedList<>();
    private Stack<List<VarTable>> Var = new Stack<>();
    private StringBuilder errorInfo = new StringBuilder();
    private boolean inLoop = false;

    public void GetfuncDeclaration(FuncTable funcTable, ASTFunctionDeclarator declarator){
        ASTVariableDeclarator variableDeclarator = (ASTVariableDeclarator) declarator.declarator;
        ASTIdentifier identifier = variableDeclarator.identifier;
        funcTable.funcName = identifier.value;
    }

    public void GetVarTable(VarTable varTable, ASTInitList node){
        ASTNode child = node.declarator;

        if(child.getClass() == ASTVariableDeclarator.class){
            varTable.name = ((ASTVariableDeclarator) child).identifier.value;
            if(node.exprs != null){
                varTable.value = node.exprs.get(0);
            }
        }
        else if(child.getClass() == ASTArrayDeclarator.class){
            while (child.getClass() != ASTVariableDeclarator.class){
                child = ((ASTArrayDeclarator) child).declarator;
            }
            varTable.name = ((ASTVariableDeclarator) child).identifier.value;
        }
    }

    public void visit(ASTCompilationUnit astCompilationUnit){
        for(ASTNode child : astCompilationUnit.items){
            if(child instanceof ASTDeclaration){
                child.parent = astCompilationUnit;
                visit((ASTDeclaration) child);
            }
            else if(child instanceof ASTFunctionDefine){
                visit((ASTFunctionDefine) child);
            }
        }
    }

    public void visit(ASTDeclaration astDeclaration){
        if(astDeclaration.parent.getClass() == ASTCompilationUnit.class){
            for(ASTInitList astInitList : astDeclaration.initLists){
                ASTDeclarator declarator = astInitList.declarator;

                if(declarator.getClass() == ASTFunctionDeclarator.class){
                    FuncTable funcTable = new FuncTable();
                    funcTable.varTables = new LinkedList<>();
                    GetfuncDeclaration(funcTable, (ASTFunctionDeclarator) declarator);
                    ProcTable.add(funcTable);
                }
                else{
                    VarTable varTable = new VarTable();
                    GetVarTable(varTable, astInitList);

                    for (VarTable var : GlobalVarTable){
                        if(var.name.equals(varTable.name)){
                            String Error = "ES02: Variable \""+varTable.name+"\" is already defined in this scope.\n";
                            errorInfo.append(Error);
                            break;
                        }
                    }

                    visit(varTable.value);

                    GlobalVarTable.add(varTable);
                }
            }
        }
        else if(astDeclaration.parent.getClass() == ASTIterationDeclaredStatement.class){
            for(ASTInitList astInitList : astDeclaration.initLists){
                VarTable varTable = new VarTable();
                GetVarTable(varTable, astInitList);

                for (VarTable var : Var.peek()){
                    if(var.name.equals(varTable.name)){
                        String Error="ES02: Variable \""+varTable.name+"\" is already defined in this scope.\n";
                        errorInfo.append(Error);
                        break;
                    }
                }

                visit(varTable.value);

                Var.peek().add(varTable);
            }
        }
        else if(astDeclaration.parent.getClass() == ASTCompoundStatement.class){
            for(ASTInitList astInitList : astDeclaration.initLists){
                VarTable varTable = new VarTable();
                GetVarTable(varTable, astInitList);

                for (VarTable var : Var.peek()){
                    if(var.name.equals(varTable.name)){
                        String Error="ES02: Variable \""+varTable.name+"\" is already defined in this scope.\n";
                        errorInfo.append(Error);
                        break;
                    }
                }

                visit(varTable.value);

                Var.peek().add(varTable);
            }
        }
        else{
            ASTCompoundStatement astCompoundStatement = (ASTCompoundStatement) astDeclaration.parent;
            ASTFunctionDefine astFunctionDefine = (ASTFunctionDefine) astCompoundStatement.parent;
            ASTFunctionDeclarator astFunctionDeclarator = (ASTFunctionDeclarator) astFunctionDefine.declarator;
            ASTVariableDeclarator astVariableDeclarator = (ASTVariableDeclarator) astFunctionDeclarator.declarator;
            ASTIdentifier astIdentifier = astVariableDeclarator.identifier;

            for(ASTInitList astInitList : astDeclaration.initLists){
                VarTable varTable = new VarTable();
                GetVarTable(varTable, astInitList);
                visit(varTable.value);

                for(FuncTable funcTable : ProcTable){
                    if(funcTable.funcName.equals(astIdentifier.value)){
                        funcTable.varTables.add(varTable);
                    }
                }
            }
        }
    }

    public void visit(ASTFunctionDefine astFunctionDefine){
        Var.push(new LinkedList<>());

        FuncTable funcTable = new FuncTable();
        ASTFunctionDeclarator astFunctionDeclarator = (ASTFunctionDeclarator) astFunctionDefine.declarator;
        ASTVariableDeclarator astVariableDeclarator = (ASTVariableDeclarator) astFunctionDeclarator.declarator;

        for(int i=0; i<astFunctionDeclarator.params.size(); i++){
            VarTable varTable = new VarTable();
            ASTParamsDeclarator astParamsDeclarator = astFunctionDeclarator.params.get(i);
            ASTVariableDeclarator param = (ASTVariableDeclarator) astParamsDeclarator.declarator;
            varTable.name = param.identifier.value;
            funcTable.varTables.add(varTable);
            Var.peek().add(varTable);
        }

        ASTIdentifier astIdentifier = astVariableDeclarator.identifier;
        funcTable.funcName = astIdentifier.value;

        for(FuncTable func : ProcTable){
            if(func.funcName.equals(funcTable.funcName)){
                String Error="ES02: Function \""+funcTable.funcName+"\" is already defined in this scope.\n";
                errorInfo.append(Error);
                break;
            }
        }

        ProcTable.add(funcTable);

        astFunctionDefine.body.parent = astFunctionDefine;
        visit(astFunctionDefine.body);

        Var.pop();
    }

    public void visit(ASTExpression expression){
        if(expression instanceof ASTArrayAccess) {
            visit((ASTArrayAccess)expression);
        }else if(expression instanceof ASTBinaryExpression) {
            visit((ASTBinaryExpression)expression);
        }else if(expression instanceof ASTCastExpression) {
            visit((ASTCastExpression)expression);
        }else if(expression instanceof ASTConditionExpression) {
            visit((ASTConditionExpression)expression);
        }else if(expression instanceof ASTFunctionCall) {
            visit((ASTFunctionCall)expression);
        }else if(expression instanceof ASTIdentifier) {
            visit((ASTIdentifier)expression);
        }else if(expression instanceof ASTMemberAccess) {
            visit((ASTMemberAccess)expression);
        }else if(expression instanceof ASTPostfixExpression) {
            visit((ASTPostfixExpression)expression);
        }else if(expression instanceof ASTUnaryExpression) {
            visit((ASTUnaryExpression)expression);
        }else if(expression instanceof ASTUnaryTypename){
            visit((ASTUnaryTypename)expression);
        }
    }

    public void visit(ASTUnaryExpression astUnaryExpression){
        visit(astUnaryExpression.expr);
    }

    public void visit(ASTPostfixExpression astPostfixExpression){
        visit(astPostfixExpression.expr);
    }

    public void visit(ASTBinaryExpression astBinaryExpression){
        String op = astBinaryExpression.op.value;

        if (op.equals("=")||op.equals("+=")||op.equals("-=")||op.equals("*=") ||op.equals("/=") || op.equals("%=") || op.equals("<<=") ||op.equals(">>=") ||op.equals("&=") ||op.equals("^=") ||op.equals("|=")) {
            visit(astBinaryExpression.expr1);

            if(astBinaryExpression.expr2 instanceof ASTBinaryExpression) {
                ASTBinaryExpression value = (ASTBinaryExpression) astBinaryExpression.expr2;
                visit(value.expr1);
                visit(value.expr2);
            }
            else if(astBinaryExpression.expr2 instanceof ASTUnaryExpression){
                ASTUnaryExpression value = (ASTUnaryExpression) astBinaryExpression.expr2;
                visit(value);
            }
            else if(astBinaryExpression.expr2 instanceof ASTPostfixExpression){
                ASTPostfixExpression value = (ASTPostfixExpression) astBinaryExpression.expr2;
                visit(value);
            }
            else {
                visit(astBinaryExpression.expr2);
            }
        }
        else {
            visit(astBinaryExpression.expr1);
            visit(astBinaryExpression.expr2);
        }
    }

    public void visit(ASTIdentifier astIdentifier){
        boolean flag = false;
        if(!Var.peek().isEmpty()){
            for(VarTable varTable : Var.peek()){
                if(astIdentifier.value.equals(varTable.name)){
                    flag = true;
                    break;
                }
            }
        }

        FuncTable funcTable = ProcTable.get(ProcTable.size()-1);

        if(!funcTable.varTables.isEmpty() && !flag){
            for(VarTable varTable : funcTable.varTables){
                if(astIdentifier.value.equals(varTable.name)){
                    flag = true;
                    break;
                }
            }
        }

        if(!GlobalVarTable.isEmpty() && !flag){
            for(VarTable varTable : GlobalVarTable){
                if(astIdentifier.value.equals(varTable.name)){
                    System.out.println();
                    flag = true;
                    break;
                }
            }
        }

        if(!flag){
            String Error="ES01: Identifier \""+astIdentifier.value+"\" is undefined.\n";
            errorInfo.append(Error);
        }
    }

    public void visit(ASTFunctionCall astFunctionCall){
        if(astFunctionCall.argList != null){
            for(int i=0; i<astFunctionCall.argList.size(); i++){
                ASTExpression astExpression = astFunctionCall.argList.get(i);
                visit(astExpression);
            }
        }

        boolean flag = false;
        for(FuncTable funcTable : ProcTable){
            if(funcTable.funcName.equals(((ASTIdentifier) astFunctionCall.funcname).value)){
                flag = true;
                break;
            }
        }

        if(!flag){
            String Error = "ES01: Identifier \""+((ASTIdentifier) astFunctionCall.funcname).value+"\" is undefined.\n";
            errorInfo.append(Error);
        }
    }

    public void visit(ASTArrayAccess astArrayAccess){
        visit(astArrayAccess.elements.get(0));
        ASTExpression astExpression = astArrayAccess.arrayName;

        if(astExpression.getClass()==ASTIdentifier.class){
            boolean flag = false;
            if(!Var.peek().isEmpty()){
                for(VarTable varTable : Var.peek()){
                    if(((ASTIdentifier) astExpression).value.equals(varTable.name)){
                        flag = true;
                        break;
                    }
                }
            }

            FuncTable funcTable = ProcTable.get(ProcTable.size()-1);

            if(!funcTable.varTables.isEmpty() && !flag){
                for(VarTable varTable : funcTable.varTables){
                    if(((ASTIdentifier) astExpression).value.equals(varTable.name)){
                        flag = true;
                        break;
                    }
                }
            }

            if(!GlobalVarTable.isEmpty() && !flag){
                for(VarTable varTable : GlobalVarTable){
                    if(((ASTIdentifier) astExpression).value.equals(varTable.name)){
                        flag = true;
                        break;
                    }
                }
            }

            if(!flag){
                String Error = "ES01: Identifier \""+((ASTIdentifier) astExpression).value+"\" is undefined.\n";
                errorInfo.append(Error);
            }
        }
        else{
            visit(astExpression);
        }
    }

    public void visit(ASTStatement statement) {
        if(statement instanceof ASTIterationDeclaredStatement) {
            visit((ASTIterationDeclaredStatement)statement);
        }else if(statement instanceof ASTIterationStatement) {
            visit((ASTIterationStatement)statement);
        }else if(statement instanceof ASTCompoundStatement) {
            visit((ASTCompoundStatement)statement);
        }else if(statement instanceof ASTSelectionStatement) {
            visit((ASTSelectionStatement)statement);
        }else if(statement instanceof ASTExpressionStatement) {
            visit((ASTExpressionStatement)statement);
        }else if(statement instanceof ASTBreakStatement) {
            visit((ASTBreakStatement)statement);
        }else if(statement instanceof ASTReturnStatement) {
            visit((ASTReturnStatement) statement);
        }
    }

    public void visit(ASTCompoundStatement astCompoundStatement){
        for(ASTNode blockItem : astCompoundStatement.blockItems){
            if(blockItem instanceof ASTDeclaration){
                blockItem.parent = astCompoundStatement;
                visit((ASTDeclaration) blockItem);
            }
            else if(blockItem instanceof ASTStatement){
                blockItem.parent = astCompoundStatement;
                visit((ASTStatement) blockItem);
            }
        }

        if(astCompoundStatement.parent.getClass() == ASTFunctionDefine.class){
            FuncTable funcTable = ProcTable.get(ProcTable.size()-1);
            funcTable.varTables.addAll(Var.peek());
        }
    }

    public void visit(ASTSelectionStatement astSelectionStatement){
        if (!Var.isEmpty())
            Var.push(new LinkedList<>(Var.peek()));
        else
            Var.push(new LinkedList<>());

        for(ASTExpression astExpression : astSelectionStatement.cond){
            visit(astExpression);
        }

        astSelectionStatement.then.parent = astSelectionStatement;
        visit(astSelectionStatement.then);

        if(astSelectionStatement.otherwise != null){
            visit(astSelectionStatement.otherwise);
        }

        Var.pop();
    }

    public void visit(ASTIterationDeclaredStatement astIterationDeclaredStatement){
        if (!Var.isEmpty())
            Var.push(new LinkedList<>(Var.peek()));
        else
            Var.push(new LinkedList<>());

        inLoop = true;

        if(astIterationDeclaredStatement.init != null){
            astIterationDeclaredStatement.init.parent = astIterationDeclaredStatement;
            visit(astIterationDeclaredStatement.init);
        }

        if(astIterationDeclaredStatement.cond != null){
            for (ASTExpression astExpression : astIterationDeclaredStatement.cond){
                visit(astExpression);
            }
        }

        if(astIterationDeclaredStatement.step != null){
            for(ASTExpression astExpression : astIterationDeclaredStatement.step){
                visit(astExpression);
            }
        }

        if(astIterationDeclaredStatement.stat != null){
            astIterationDeclaredStatement.stat.parent = astIterationDeclaredStatement;
            visit(astIterationDeclaredStatement.stat);
        }

        inLoop = false;
        Var.pop();
    }

    public void visit(ASTIterationStatement astIterationStatement){
        if (!Var.isEmpty())
            Var.push(new LinkedList<>(Var.peek()));
        else
            Var.push(new LinkedList<>());

        inLoop = true;

        if(astIterationStatement.init != null){
            for (ASTExpression astExpression : astIterationStatement.init){
                visit(astExpression);
            }
        }

        if(astIterationStatement.cond != null){
            for (ASTExpression astExpression : astIterationStatement.cond){
                visit(astExpression);
            }
        }

        if(astIterationStatement.step != null){
            for(ASTExpression astExpression : astIterationStatement.step){
                visit(astExpression);
            }
        }

        if(astIterationStatement.stat != null){
            visit(astIterationStatement.stat);
        }

        inLoop = false;
        Var.pop();
    }

    public void visit(ASTExpressionStatement astExpressionStatement){
        for (ASTExpression astExpression : astExpressionStatement.exprs) {
            visit(astExpression);
        }
    }

    public void visit(ASTBreakStatement astBreakStatement){
        if(!inLoop){
            String Error="ES03: a break statement may only be used within a loop or switch.\n";
            errorInfo.append(Error);
        }
    }

    public void visit(ASTReturnStatement astReturnStatement){
        if(astReturnStatement.expr!=null && !astReturnStatement.expr.isEmpty()){
            for(ASTExpression astExpression : astReturnStatement.expr){
                visit(astExpression);
            }
        }
    }

    public void visit(ASTLabeledStatement astLabeledStatement){
        if(astLabeledStatement.stat != null){
            visit(astLabeledStatement.stat);
        }
    }

    public String getErrorInfo(){
        return errorInfo.toString();
    }
}