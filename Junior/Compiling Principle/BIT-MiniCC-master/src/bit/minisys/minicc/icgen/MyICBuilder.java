package bit.minisys.minicc.icgen;

import java.util.*;

import bit.minisys.minicc.parser.ast.*;

public class MyICBuilder {
    private int tmpRegID = 0;
    private int itLabelID = 0;
    private int ifLabelID = 0;
    private Map<ASTNode, ASTNode> map = new HashMap<>();
    private List<Quat> quats = new LinkedList<>();

    public MyICBuilder() {
    }

    public List<Quat> getQuats() {
        return quats;
    }

    public void visit(ASTCompilationUnit program) {
        for (ASTNode node : program.items) {
            if (node instanceof ASTFunctionDefine)
                visit((ASTFunctionDefine) node);
            else if (node instanceof ASTDeclaration) {
                node.parent = program;
                visit((ASTDeclaration) node);
            }
        }
    }

    public void visit(ASTDeclaration declaration) {
        for (ASTInitList astInitList : declaration.initLists) {
            ASTNode node = astInitList.declarator;
            if (node.getClass() == ASTVariableDeclarator.class && !astInitList.exprs.isEmpty()) {
                visit(astInitList.exprs.get(0));
                ASTNode opnd = map.get(astInitList.exprs.get(0));
                Quat quat = new Quat("=", ((ASTVariableDeclarator) node).identifier, opnd, null);
                quats.add(quat);
            }
        }
    }

    public void visit(ASTArrayAccess arrayAccess) {
        ASTNode opnd1, opnd2;

        visit(arrayAccess.elements.get(0));
        opnd2 = map.get(arrayAccess.elements.get(0));
        ASTExpression astExpression = arrayAccess.arrayName;

        if (astExpression.getClass() == ASTIdentifier.class) {
            opnd1 = astExpression;
            map.put(arrayAccess.arrayName, astExpression);
        } else {
            visit(astExpression);
            opnd1 = map.get(astExpression);
        }
        TemporaryValue res = new TemporaryValue(++tmpRegID);
        map.put(arrayAccess, res);
        Quat quat = new Quat("[]", res, opnd1, opnd2);
        quats.add(quat);
    }

    public void visit(ASTBinaryExpression binaryExpression) {
        String op = binaryExpression.op.value;
        ASTNode res;
        ASTNode opnd1 = null;
        ASTNode opnd2 = null;

        if (op.equals("=") || op.equals("+=") || op.equals("-=") || op.equals("*=") || op.equals("/=") || op.equals("%=") || op.equals("<<=") || op.equals(">>=") || op.equals("&=") || op.equals("^=") || op.equals("|=")) {
            visit(binaryExpression.expr1);
            res = map.get(binaryExpression.expr1);
            if (binaryExpression.expr2 instanceof ASTIdentifier) {
                opnd1 = binaryExpression.expr2;
            } else if (binaryExpression.expr2 instanceof ASTIntegerConstant) {
                opnd1 = binaryExpression.expr2;
            } else if (binaryExpression.expr2 instanceof ASTStringConstant) {
                opnd1 = binaryExpression.expr2;
            } else if (binaryExpression.expr2 instanceof ASTBinaryExpression) {
                ASTBinaryExpression value = (ASTBinaryExpression) binaryExpression.expr2;
                op = value.op.value;
                visit(value.expr1);
                opnd1 = map.get(value.expr1);
                visit(value.expr2);
                opnd2 = map.get(value.expr2);
            } else if (binaryExpression.expr2 instanceof ASTUnaryExpression) {
                ASTUnaryExpression value = (ASTUnaryExpression) binaryExpression.expr2;
                op = value.op.value;
                visit(value);
                opnd1 = map.get(value.expr);
            } else if (binaryExpression.expr2 instanceof ASTPostfixExpression) {
                ASTPostfixExpression value = (ASTPostfixExpression) binaryExpression.expr2;
                op = value.op.value;
                visit(value);
                opnd2 = map.get(value.expr);
            } else {
                visit(binaryExpression.expr2);
                opnd1 = map.get(binaryExpression.expr2);
            }
        } else {
            res = new TemporaryValue(++tmpRegID);
            visit(binaryExpression.expr1);
            opnd1 = map.get(binaryExpression.expr1);
            visit(binaryExpression.expr2);
            opnd2 = map.get(binaryExpression.expr2);
        }

        Quat quat = new Quat(op, res, opnd1, opnd2);
        quats.add(quat);
        map.put(binaryExpression, res);
    }

    public void visit(ASTBreakStatement breakStat) {
        quats.add(new Quat("Break", null, null, null));
    }

    public void visit(ASTContinueStatement continueStatement) {
        quats.add(new Quat("Continue", null, null, null));
    }

    public void visit(ASTCompoundStatement compoundStat) {
        for (ASTNode node : compoundStat.blockItems) {
            if (node instanceof ASTDeclaration) {
                node.parent = compoundStat;
                visit((ASTDeclaration) node);
            } else if (node instanceof ASTStatement) {
                visit((ASTStatement) node);
            }
        }
    }

    public void visit(ASTExpression expression) {
        if (expression instanceof ASTArrayAccess) {
            visit((ASTArrayAccess) expression);
        } else if (expression instanceof ASTBinaryExpression) {
            visit((ASTBinaryExpression) expression);
        } else if (expression instanceof ASTCastExpression) {
            visit((ASTCastExpression) expression);
        } else if (expression instanceof ASTCharConstant) {
            visit((ASTCharConstant) expression);
        } else if (expression instanceof ASTConditionExpression) {
            visit((ASTConditionExpression) expression);
        } else if (expression instanceof ASTFloatConstant) {
            visit((ASTFloatConstant) expression);
        } else if (expression instanceof ASTFunctionCall) {
            visit((ASTFunctionCall) expression);
        } else if (expression instanceof ASTIdentifier) {
            visit((ASTIdentifier) expression);
        } else if (expression instanceof ASTIntegerConstant) {
            visit((ASTIntegerConstant) expression);
        } else if (expression instanceof ASTMemberAccess) {
            visit((ASTMemberAccess) expression);
        } else if (expression instanceof ASTPostfixExpression) {
            visit((ASTPostfixExpression) expression);
        } else if (expression instanceof ASTStringConstant) {
            visit((ASTStringConstant) expression);
        } else if (expression instanceof ASTUnaryExpression) {
            visit((ASTUnaryExpression) expression);
        } else if (expression instanceof ASTUnaryTypename) {
            visit((ASTUnaryTypename) expression);
        }
    }

    public void visit(ASTExpressionStatement expressionStat) {
        for (ASTExpression node : expressionStat.exprs) {
            visit((ASTExpression) node);
        }
    }

    public void visit(ASTFunctionCall funcCall) {
        if (funcCall.argList != null) {
            for (int i = 0; i < funcCall.argList.size(); i++) {
                ASTExpression astExpression = funcCall.argList.get(i);
                visit(astExpression);
                ASTNode opnd = map.get(astExpression);
                quats.add(new Quat("param", null, opnd, null));
            }
        }
        Quat quat = new Quat("call", funcCall.funcname, null, null);
        quats.add(quat);
    }

    public void visit(ASTGotoStatement gotoStat) {
        if (gotoStat.label != null) {
            ASTNode res = new LabelGenerator(0, gotoStat.label.value);
            quats.add(new Quat("goto", res, null, null));
        }
    }

    public void visit(ASTIdentifier identifier) {
        map.put(identifier, identifier);
    }

    public void visit(ASTIntegerConstant intConst) {
        map.put(intConst, intConst);
    }

    public void visit(ASTIterationDeclaredStatement iterationDeclaredStat) {
        itLabelID++;
        ASTNode loopStartLabel = new LabelGenerator(itLabelID, "loopStart");
        ASTNode loopCheckLabel = new LabelGenerator(itLabelID, "loopCheck");
        ASTNode loopNextLabel = new LabelGenerator(itLabelID, "loopNext");
        ASTNode loopEndLabel = new LabelGenerator(itLabelID, "loopEnd");

        quats.add(new Quat("Label", loopStartLabel, null, null));

        if (iterationDeclaredStat.init != null) {
            iterationDeclaredStat.init.parent = iterationDeclaredStat;
            visit(iterationDeclaredStat.init);
        }

        quats.add(new Quat("Label", loopCheckLabel, null, null));

        if (iterationDeclaredStat.cond != null) {
            for (ASTExpression astExpression : iterationDeclaredStat.cond) {
                visit(astExpression);
            }

            quats.add(new Quat("JF", loopEndLabel, null, null));
        }

        if (iterationDeclaredStat.stat != null) {
            visit(iterationDeclaredStat.stat);
        }

        quats.add(new Quat("Label", loopNextLabel, null, null));

        if (iterationDeclaredStat.step != null) {
            for (ASTExpression astExpression : iterationDeclaredStat.step) {
                visit(astExpression);
            }
        }

        quats.add(new Quat("Label", loopEndLabel, null, null));
    }

    public void visit(ASTIterationStatement iterationStat) {
        itLabelID++;
        ASTNode loopStartLabel = new LabelGenerator(itLabelID, "loopStart");
        ASTNode loopCheckLabel = new LabelGenerator(itLabelID, "loopCheck");
        ASTNode loopNextLabel = new LabelGenerator(itLabelID, "loopNext");
        ASTNode loopEndLabel = new LabelGenerator(itLabelID, "loopEnd");

        quats.add(new Quat("Label", loopStartLabel, null, null));

        if (iterationStat.init != null) {
            for (ASTExpression astExpression : iterationStat.init) {
                visit(astExpression);
            }
        }

        quats.add(new Quat("Label", loopCheckLabel, null, null));

        if (iterationStat.cond != null) {
            for (ASTExpression astExpression : iterationStat.cond) {
                visit(astExpression);
            }

            quats.add(new Quat("JF", loopEndLabel, null, null));
        }

        if (iterationStat.stat != null) {
            visit(iterationStat.stat);
        }

        quats.add(new Quat("Label", loopNextLabel, null, null));

        if (iterationStat.step != null) {
            for (ASTExpression astExpression : iterationStat.step) {
                visit(astExpression);
            }
        }

        quats.add(new Quat("Label", loopEndLabel, null, null));
    }

    public void visit(ASTLabeledStatement labeledStat) {
        if (labeledStat.label != null) {
            ASTNode res = new LabelGenerator(0, labeledStat.label.value);
            quats.add(new Quat("Label", res, null, null));
        }
        if (labeledStat.stat != null) {
            visit(labeledStat.stat);
        }
    }

    public void visit(ASTPostfixExpression postfixExpression) {
        visit(postfixExpression.expr);
        String op = postfixExpression.op.value;
        ASTNode opnd1 = map.get(postfixExpression.expr);
        quats.add(new Quat(op, opnd1, null, opnd1));
        map.put(postfixExpression, opnd1);
    }

    public void visit(ASTReturnStatement returnStat) {
        if (returnStat.expr == null || returnStat.expr.isEmpty()) {
            quats.add(new Quat("RET", null, null, null));
        } else {
            for (ASTExpression astExpression : returnStat.expr) {
                visit(astExpression);
            }
            ASTNode res = map.get(returnStat.expr.get(0));
            quats.add(new Quat("RET", res, null, null));
        }
    }

    public void visit(ASTSelectionStatement selectionStat) {
        ifLabelID++;

        ASTNode StartIfLabel = new LabelGenerator(ifLabelID, "If");
        quats.add(new Quat("Label", StartIfLabel, null, null));

        for (ASTExpression astExpression : selectionStat.cond) {
            visit(astExpression);
        }

        ASTNode ThenLabel = new LabelGenerator(ifLabelID, "Then");
        quats.add(new Quat("JT", ThenLabel, null, null));

        visit(selectionStat.then);

        if (selectionStat.otherwise != null) {
            ASTNode OtherwiseLabel = new LabelGenerator(ifLabelID, "Else");
            quats.add(new Quat("Label", OtherwiseLabel, null, null));
            visit(selectionStat.otherwise);
        }

        ifLabelID--;

        if (ifLabelID == 0) {
            ASTNode EndIfLabel = new LabelGenerator(1, "Endif");
            quats.add(new Quat("Label", EndIfLabel, null, null));
        }
    }

    public void visit(ASTStringConstant stringConst) {
        map.put(stringConst, stringConst);
    }

    public void visit(ASTUnaryExpression unaryExpression) {
        String op = unaryExpression.op.value;
        visit(unaryExpression.expr);
        ASTNode opnd1 = map.get(unaryExpression.expr);
        quats.add(new Quat(op, opnd1, null, opnd1));
        map.put(unaryExpression, opnd1);
    }

    public void visit(ASTFunctionDefine functionDefine) {
        ASTFunctionDeclarator astFunctionDeclarator = (ASTFunctionDeclarator) functionDefine.declarator;
        ASTVariableDeclarator astVariableDeclarator = (ASTVariableDeclarator) astFunctionDeclarator.declarator;

        for (int i = 0; i < astFunctionDeclarator.params.size(); i++) {
            ASTParamsDeclarator astParamsDeclarator = astFunctionDeclarator.params.get(i);
            ASTVariableDeclarator param = (ASTVariableDeclarator) astParamsDeclarator.declarator;
            ASTNode opnd1 = param.identifier;
            quats.add(new Quat("param", null, opnd1, null));
        }

        quats.add(new Quat("func", astVariableDeclarator.identifier, null, null));
        visit(functionDefine.body);
    }

    public void visit(ASTStatement statement) {
        if (statement instanceof ASTIterationDeclaredStatement) {
            visit((ASTIterationDeclaredStatement) statement);
        } else if (statement instanceof ASTIterationStatement) {
            visit((ASTIterationStatement) statement);
        } else if (statement instanceof ASTCompoundStatement) {
            visit((ASTCompoundStatement) statement);
        } else if (statement instanceof ASTSelectionStatement) {
            visit((ASTSelectionStatement) statement);
        } else if (statement instanceof ASTExpressionStatement) {
            visit((ASTExpressionStatement) statement);
        } else if (statement instanceof ASTBreakStatement) {
            visit((ASTBreakStatement) statement);
        } else if (statement instanceof ASTContinueStatement) {
            visit((ASTContinueStatement) statement);
        } else if (statement instanceof ASTReturnStatement) {
            visit((ASTReturnStatement) statement);
        } else if (statement instanceof ASTGotoStatement) {
            visit((ASTGotoStatement) statement);
        } else if (statement instanceof ASTLabeledStatement) {
            visit((ASTLabeledStatement) statement);
        }
    }
}